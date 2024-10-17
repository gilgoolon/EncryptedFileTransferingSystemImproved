#pragma once
#include "../../Common/Buffer.hpp"

class IDeserializable {
public:
	virtual ~IDeserializable() = default;

	virtual void deserialize(const buffer::Buffer& data) = 0;
};

uint8_t deserialize_uint8(buffer::Buffer::const_iterator data);

uint16_t deserialize_uint16(buffer::Buffer::const_iterator data);

uint32_t deserialize_uint32(buffer::Buffer::const_iterator data);
