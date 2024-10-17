#include "Client.hpp"

#include "Common/Logging/Logger.hpp"
#include "Common/OsUtils.hpp"
#include "Common/Hex.hpp"
#include "Crypto/Rsa.hpp"
#include "Crypto/Aes.hpp"
#include "Crypto/Crc.hpp"
#include "Protocol/Requests/SignupRequest.hpp"
#include "Protocol/Requests/ReconnectRequest.hpp"
#include "Protocol/Requests/SendFileRequest.hpp"
#include "Protocol/Requests/SendFileRequest.hpp"
#include "Protocol/Requests/SendPublicKeyRequest.hpp"
#include "Protocol/Requests/CorrectCrcRequest.hpp"
#include "Protocol/Requests/IncorrectCrcSendingAgainRequest.hpp"
#include "Protocol/Requests/IncorrectCrcDoneRequest.hpp"
#include "Protocol/Protocol.hpp"
#include "Protocol/Responses/SignupSuccessResponse.hpp"
#include "Protocol/Responses/SendingAesKeyResponse.hpp"
#include "Protocol/Responses/GotFileWithCrcResponse.hpp"

static constexpr size_t MAX_SEND_FILES_RETRIES = 4;

Client::Client(const ClientInfo& client_info, std::unique_ptr<ServerCommunicator> server_communicator)
	: m_client_info(client_info)
	, m_server_communicator(std::move(server_communicator))
	, m_is_connected(false)
{
}

const ClientInfo& Client::get_client_info() const
{
	return m_client_info;
}

void Client::transfer_file(const std::filesystem::path& file_to_trasnfer)
{
	LOG_INFO("Transferring File: " + file_to_trasnfer.string());
	if (!m_is_connected) {
		throw std::runtime_error("invalid state: connect before transfering a file");
	}

	const auto file_content = os_utils::read_binary_file(file_to_trasnfer);
	const auto encrypted_content = crypto::aes::encrypt(file_content, m_aes_key);
	const auto file_checksum = crypto::crc::calculate(file_content);
	LOG_INFO(std::to_string(file_checksum));
	for (size_t i = 0; i < MAX_SEND_FILES_RETRIES; i++) {
		LOG_INFO("Try " + std::to_string(i + 1) + ": sending file");
		auto response = m_server_communicator->send_and_receive(std::make_unique<protocol::SendFileRequest>(m_client_info.id, encrypted_content, file_content.size(), file_to_trasnfer.filename().string()), protocol::ResponseCode::GOT_FILE_WITH_CRC);
		auto got_file_with_crc_response = static_cast<protocol::GotFileWithCrcResponse*>(response.get());
		if (got_file_with_crc_response->get_checksum() == file_checksum) {
			m_server_communicator->send_and_receive(std::make_unique<protocol::CorrectCrcRequest>(m_client_info.id, file_to_trasnfer.filename().string()), protocol::ResponseCode::OK_CONFIRMATION);
			LOG_INFO("Successfully transferred file");
			return;
		}
		LOG_INFO("Try " + std::to_string(i + 1) + ": failed to send file.")
	}
	m_server_communicator->send_and_receive(std::make_unique<protocol::IncorrectCrcDoneRequest>(m_client_info.id, file_to_trasnfer.filename().string()), protocol::ResponseCode::OK_CONFIRMATION);
	throw std::runtime_error("Failed to send file " + std::to_string(MAX_SEND_FILES_RETRIES) + " times");
}

void Client::connect()
{
	LOG_INFO("Connecting");
	if (m_client_info.is_registered) {
		reconnect();
	}
	else {
		sign_up();
	}
	m_is_connected = true;
	LOG_INFO("Successfully connected");
}

void Client::sign_up()
{
	LOG_INFO("Not found reconnection details, signing up...");
	auto response = m_server_communicator->send_and_receive(std::make_unique<protocol::SignupRequest>(m_client_info.name), protocol::ResponseCode::SIGNUP_SUCCESS);
	m_client_info.id = static_cast<protocol::SignupSuccessResponse*>(response.get())->get_client_id();

	LOG_INFO("SignSuccess received, client id: " + hex::encode(m_client_info.id));

	buffer::Buffer public_key;
	crypto::rsa::generate_key_pair(m_client_info.private_key, public_key);

	response = m_server_communicator->send_and_receive(std::make_unique<protocol::SendPublicKeyRequest>(m_client_info.id, m_client_info.name, public_key), protocol::ResponseCode::SENDING_AES_KEY);
	m_aes_key = static_cast<protocol::SendingAesKeyResponse*>(response.get())->get_aes_key();

	LOG_INFO("SendingAesKey received");

	m_aes_key = crypto::rsa::decrypt(static_cast<protocol::SendingAesKeyResponse*>(response.get())->get_aes_key(), m_client_info.private_key);
	LOG_INFO("Successfully signed up with id " + hex::encode(m_client_info.id));
}

void Client::reconnect()
{
	LOG_INFO("Already signed up with id " + hex::encode(m_client_info.id) + ", reconnecting...");
	auto response = m_server_communicator->send_and_receive(std::make_unique<protocol::ReconnectRequest>(m_client_info.id, m_client_info.name), protocol::ResponseCode::RECONNECT_SUCCESS_SENDING_AES);
	
	m_aes_key = crypto::rsa::decrypt(static_cast<protocol::SendingAesKeyResponse*>(response.get())->get_aes_key(), m_client_info.private_key);
	LOG_INFO("Successfully reconnected");
}
