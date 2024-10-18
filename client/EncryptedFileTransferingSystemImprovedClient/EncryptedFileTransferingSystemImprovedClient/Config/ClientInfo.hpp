#pragma once
#include <optional>
#include <string>
#include <filesystem>

#include "../Common/Buffer.hpp"

namespace config {
struct ClientInfo {
	std::string name;
	buffer::Buffer id;
	buffer::Buffer private_key;
	bool is_registered = false;

	std::string serialize() const;
};

ClientInfo make_client_info(const std::filesystem::path& me_info_path);

};
