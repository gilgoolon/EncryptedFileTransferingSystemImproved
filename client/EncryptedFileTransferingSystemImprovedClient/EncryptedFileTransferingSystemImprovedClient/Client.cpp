#include "Client.hpp"

#include "Common/Logging/Logger.hpp"

Client::Client(const ClientInfo client_info, std::unique_ptr<ServerCommunicator> server_communicator, std::filesystem::path file_to_transfer)
	: m_client_info(client_info)
	, m_server_communicator(std::move(server_communicator))
	, m_file_to_trasnfer(std::move(file_to_transfer))
{
}

void Client::run()
{
	INFO("Running")
	


}
