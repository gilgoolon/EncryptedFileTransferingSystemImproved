#include "Client.hpp"

#include "Common/Logging/Logger.hpp"
#include "Protocol/Requests/SignupRequest.hpp"
#include "Protocol/Requests/ReconnectRequest.hpp"
#include "Protocol/Protocol.hpp"
#include "Protocol/Responses/SignupSuccessResponse.hpp"
#include "Common/Hex.hpp"

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
	auto response = m_server_communicator->send_and_receive(std::make_unique<protocol::SignupRequest>(m_client_info.id, m_client_info.name), protocol::ResponseCode::SIGNUP_SUCCESS);
	const auto* singup_success_response = static_cast<protocol::SignupSuccessResponse*>(response.get());
	m_client_info.id = singup_success_response->get_client_id();

	INFO("Successfully signed up with id " + hex::encode(m_client_info.id));
}

void Client::reconnect()
{
	INFO("Already signed up with id " + hex::encode(m_client_info.id) + ", reconnecting...");
}
