#include <filesystem>

#include "Configurator.hpp"
#include <iostream>
#include "Common/OsUtils.hpp"

std::filesystem::path TRANSFER_INFO_PATH = "transfer.info";
std::filesystem::path ME_INFO_PATH = "me.info";

int main()
{	
	std::unique_ptr<Client> client;
	try {
		configurator::make_client(TRANSFER_INFO_PATH, ME_INFO_PATH);
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to configure client. Error: " << ex.what() << std::endl;
	}
	try {
		if (!client->connect()) {
			os_utils::write_text_file(TRANSFER_INFO_PATH, client->get_client_info().serialize());
		}
		client->run();
	}
	catch (const std::exception& ex) {
		std::cout << "Error while running client: " << ex.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
