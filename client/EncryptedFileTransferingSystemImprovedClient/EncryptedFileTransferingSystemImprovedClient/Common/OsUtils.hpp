#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <filesystem>

#include "Buffer.hpp"

namespace os_utils{

	buffer::Buffer read_binary_file(const std::filesystem::path& path);

	std::string read_text_file(const std::filesystem::path& path);
	
	uint64_t read_uint64_from_file(const std::filesystem::path& path);

	void write_text_file(const std::filesystem::path& path, const std::string& text);
};
