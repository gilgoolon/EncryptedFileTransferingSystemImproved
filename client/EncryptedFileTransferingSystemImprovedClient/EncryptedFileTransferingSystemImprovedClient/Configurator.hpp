#pragma once
#include <filesystem>

#include "Client.hpp"

namespace configurator {
	std::unique_ptr<Client> make_client(const std::filesystem::path& transfer_info_path, const std::filesystem::path& me_info_path);

	ClientInfo make_client_info(const std::filesystem::path& me_info_path);
};