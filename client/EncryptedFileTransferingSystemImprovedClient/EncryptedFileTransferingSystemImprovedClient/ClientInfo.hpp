#pragma once
#include <optional>
#include <string>

#include "Common/Buffer.hpp"

struct ClientInfo {
	std::string name;
	buffer::Buffer id;
	buffer::Buffer private_key;
	bool is_registered = false;

	std::string serialize() const;
};
