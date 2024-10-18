#pragma once
#include <filesystem>

#include "Config/ClientInfo.hpp"
using config::ClientInfo;
#include "ServerCommunicator.hpp"

class Client final {
public:
	explicit Client(const ClientInfo& client_info, std::unique_ptr<ServerCommunicator> server_communicator);

	const ClientInfo& get_client_info() const;

	void transfer_file(const std::filesystem::path& file_to_trasnfer);

	void connect();

private:
	ClientInfo m_client_info;
	std::unique_ptr<ServerCommunicator> m_server_communicator;
	bool m_is_connected;
	buffer::Buffer m_aes_key;

	void sign_up();

	void reconnect();
};
