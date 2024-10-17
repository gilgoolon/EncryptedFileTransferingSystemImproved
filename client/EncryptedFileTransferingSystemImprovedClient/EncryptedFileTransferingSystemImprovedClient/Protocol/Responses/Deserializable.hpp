#pragma once
#include <iostream>
#include "../../Common/Buffer.hpp"

class IDeserializable {
public:
	virtual ~IDeserializable() = default;

	virtual void deserialize(const buffer::Buffer& data) = 0;
};

template <typename UintType>
UintType deserialize_uint(buffer::Buffer::const_iterator data) {
    UintType result = 0;
    for (size_t i = 0; i < sizeof(UintType); i++, data++) {
        result |= static_cast<UintType>(*data) << (i * 8);
        result <<= 8;
    }
    std::cout << "Result: " << result << std::endl;
    return result;
}
