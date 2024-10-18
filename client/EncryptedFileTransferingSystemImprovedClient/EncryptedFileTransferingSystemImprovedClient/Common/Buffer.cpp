#include "Buffer.hpp"
using buffer::Buffer;

std::string buffer::to_string(const Buffer& buffer)
{
	return std::string(buffer.begin(), buffer.end());
}

Buffer buffer::to_buffer(const std::string& str)
{
	return Buffer(str.begin(), str.end());
}
