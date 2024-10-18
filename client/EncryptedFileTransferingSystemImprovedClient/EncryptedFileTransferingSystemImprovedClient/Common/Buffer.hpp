#pragma once
#include <vector>
#include <string>

namespace buffer {
	using Byte = uint8_t;
	using Buffer = std::vector<Byte>;

	std::string to_string(const Buffer& buffer);

	Buffer to_buffer(const std::string& str);
};
