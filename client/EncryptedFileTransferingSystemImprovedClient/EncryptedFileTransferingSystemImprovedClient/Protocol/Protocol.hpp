#pragma once
#include "Responses/Response.hpp"

namespace protocol {
	static constexpr size_t CLIENT_ID_SIZE = 16;
	static constexpr size_t CLIENT_NAME_SIZE = 255;
	static constexpr size_t FILENAME_SIZE = 255;
	
	std::unique_ptr<Response> make_response(const buffer::Buffer& data);
};
