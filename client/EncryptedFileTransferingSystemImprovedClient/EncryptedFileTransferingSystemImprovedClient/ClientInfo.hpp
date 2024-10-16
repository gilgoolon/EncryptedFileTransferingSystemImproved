#pragma once
#include <optional>
#include <string>

#include "Common/Buffer.hpp"

struct ClientInfo {
	std::string name;
	std::optional<buffer::Buffer> id;
	std::optional<buffer::Buffer> private_key;
};
