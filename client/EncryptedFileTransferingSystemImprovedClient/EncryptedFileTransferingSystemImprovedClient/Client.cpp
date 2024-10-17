#include "Client.hpp"

#include "Common/Logging/Logger.hpp"
#include "Protocol/Responses/Response.hpp"
#include "Protocol/Requests/SignupRequest.hpp"
#include "Protocol/Requests/ReconnectRequest.hpp"

Client::Client(const ClientInfo client_info, std::unique_ptr<ServerCommunicator> server_communicator, std::filesystem::path file_to_transfer)
	: m_client_info(client_info)
	, m_server_communicator(std::move(server_communicator))
	, m_file_to_trasnfer(std::move(file_to_transfer))
{
}

void Client::run()
{
	INFO("Running");
	
	if (m_client_info.is_registered) {
		reconnect();
	}
	else {
		signup();
	}
}

void Client::signup()
{
	protocol::SignupRequest signup_request(m_client_info.id, m_client_info.name);
}

void Client::reconnect()
{
}
