#include "Client.hpp"

#include "Common/Logging/Logger.hpp"
#include "Common/Hex.hpp"
#include "Crypto/Rsa.hpp"
#include "Protocol/Requests/SignupRequest.hpp"
#include "Protocol/Requests/ReconnectRequest.hpp"
#include "Protocol/Protocol.hpp"
#include "Protocol/Responses/SignupSuccessResponse.hpp"
#include "Protocol/Requests/SendPublicKeyRequest.hpp"
#include "Protocol/Responses/SendingAesKeyResponse.hpp"

Client::Client(const ClientInfo client_info, std::unique_ptr<ServerCommunicator> server_communicator, std::filesystem::path file_to_transfer)
	: m_client_info(client_info)
	, m_server_communicator(std::move(server_communicator))
	, m_file_to_trasnfer(std::move(file_to_transfer))
	, m_is_connected(false)
{
}

const ClientInfo& Client::get_client_info() const
{
	return m_client_info;
}

bool Client::connect()
{
	INFO("Connecting");
	if (m_client_info.is_registered) {
		reconnect();
	}
	else {
		sign_up();
	}
	m_is_connected = true;
	INFO("Successfully connected");
	return m_client_info.is_registered;
}

void Client::run()
{
	INFO("Running");
	if (!m_is_connected) {
		throw std::runtime_error("invalid state: connect before running the client");
	}

	INFO("Successfully ran");
}

void Client::sign_up()
{
	INFO("Not found reconnection details, signing up...");
	auto response = m_server_communicator->send_and_receive(std::make_unique<protocol::SignupRequest>(m_client_info.name), protocol::ResponseCode::SIGNUP_SUCCESS);
	m_client_info.id = static_cast<protocol::SignupSuccessResponse*>(response.get())->get_client_id();

	buffer::Buffer public_key;
	crypto::rsa::generate_key_pair(m_client_info.private_key, public_key);

	response = m_server_communicator->send_and_receive(std::make_unique<protocol::SendPublicKeyRequest>(m_client_info.id, m_client_info.name, public_key), protocol::ResponseCode::SENDING_AES_KEY);
	m_aes_key = static_cast<protocol::SendingAesKeyResponse*>(response.get())->get_aes_key();

	m_aes_key = crypto::rsa::decrypt(static_cast<protocol::SignupSuccessResponse*>(response.get())->get_client_id(), m_client_info.private_key);
	INFO("Successfully signed up with id " + hex::encode(m_client_info.id));
}

void Client::reconnect()
{
	INFO("Already signed up with id " + hex::encode(m_client_info.id) + ", reconnecting...");
	auto response = m_server_communicator->send_and_receive(std::make_unique<protocol::ReconnectRequest>(m_client_info.id, m_client_info.name), protocol::ResponseCode::RECONNECT_SUCCESS_SENDING_AES);
	m_client_info.id = static_cast<protocol::SignupSuccessResponse*>(response.get())->get_client_id();

	buffer::Buffer public_key;
	crypto::rsa::generate_key_pair(m_client_info.private_key, public_key);

	response = m_server_communicator->send_and_receive(std::make_unique<protocol::SendPublicKeyRequest>(m_client_info.id, m_client_info.name, public_key), protocol::ResponseCode::SENDING_AES_KEY);
	m_aes_key = static_cast<protocol::SendingAesKeyResponse*>(response.get())->get_aes_key();

	m_aes_key = crypto::rsa::decrypt(static_cast<protocol::SignupSuccessResponse*>(response.get())->get_client_id(), m_client_info.private_key);
}
