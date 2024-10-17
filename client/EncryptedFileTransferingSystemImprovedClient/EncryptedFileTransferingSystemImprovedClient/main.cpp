#include <iostream>
#include <filesystem>

#include "Config/Configurator.hpp"
#include "Common/OsUtils.hpp"

std::filesystem::path TRANSFER_INFO_PATH = "transfer.info";
std::filesystem::path ME_INFO_PATH = "me.info";

int main()
{
	const auto transfer_info = config::make_transfer_info(TRANSFER_INFO_PATH);
	ClientInfo client_info;
	client_info.name = transfer_info.client_name;
	if (std::filesystem::exists(ME_INFO_PATH)) {
		client_info = config::make_client_info(ME_INFO_PATH);
	}

	std::unique_ptr<Client> client;
	try {
		config::make_client(client_info, transfer_info);
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to configure client. Error: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	try {
		client->connect();
		client_info = client->get_client_info();
		if (!client_info.is_registered) {
			os_utils::write_text_file(TRANSFER_INFO_PATH, client->get_client_info().serialize());
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Error while connecting to server: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	try {
		client->transfer_file(transfer_info.file_to_transfer);
	}
	catch (const std::exception& ex) {
		std::cout << "Error while transferring file: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
