#include "Deserializable.hpp"

uint8_t deserialize_uint8(buffer::Buffer::const_iterator data)
{
	return *data;
}

uint16_t deserialize_uint16(buffer::Buffer::const_iterator data)
{
	uint16_t result = 0;
	result |= data[0];
	result |= data[1] << 8;
	return result;
}

uint32_t deserialize_uint32(buffer::Buffer::const_iterator data)
{
	uint32_t result = 0;
	result |= data[0];
	result |= data[1] << 8;
	result |= data[2] << 16;
	result |= data[3] << 24;
	return result;
}
