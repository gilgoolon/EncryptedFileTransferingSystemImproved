#pragma once
#include <filesystem>

#include "ClientInfo.hpp"
#include "ServerCommunicator.hpp"


class Client final {
public:
	explicit Client(const ClientInfo client_info, std::unique_ptr<ServerCommunicator> server_communicator, std::filesystem::path file_to_trasnfer);

	const ClientInfo& get_client_info() const;

	bool connect();

	void run();

private:
	ClientInfo m_client_info;
	std::unique_ptr<ServerCommunicator> m_server_communicator;
	std::filesystem::path m_file_to_trasnfer;
	bool m_is_connected;

	void sign_up();

	void reconnect();
};
