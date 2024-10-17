#pragma once
#include "../../Common/Buffer.hpp"

class IDeserializable {
public:
	virtual ~IDeserializable() = default;

	virtual void deserialize(const buffer::Buffer& data) = 0;
};

template <typename UintType>
UintType deserialize_uint(buffer::Buffer::const_iterator data)
{
	UintType result = 0;
	for (size_t i = 0; i < sizeof(UintType); i++, data++) {
		result <<= 8;
		result |= *data;
	}
	return result;
}
