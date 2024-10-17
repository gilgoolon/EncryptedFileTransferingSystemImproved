#pragma once
#include "../../Common/Buffer.hpp"

class ISerializable {
public:
	virtual ~ISerializable() = default;

	virtual buffer::Buffer serialize() const = 0;
};

template <typename T>
std::vector<T> concat_vectors(const std::vector<T>& first) {
    return first;
}

template <typename T, typename... Vectors>
std::vector<T> concat_vectors(const std::vector<T>& first, const Vectors&... rest) {
    std::vector<T> result = first;
    result.reserve(first.size() + (rest.size() + ...));  // Precompute total size
    (result.insert(result.end(), rest.begin(), rest.end()), ...);
    return result;
}

template <typename UintType>
buffer::Buffer serialize_uint(const UintType data)
{
    buffer::Buffer out(sizeof(data));
    for (size_t i = 0; i < out.size(); i++) {
        out[i] = (data >> (i * 8)) & 0xff;
    }
    return out;
}


//template <typename UintType>
//buffer::Buffer serialize_uint(const UintType data)
//{
//    buffer::Buffer out(sizeof(data));
//    for (size_t i = 0; i < out.size(); i++) {
//        out[i] = (data >> (out.size() - i - 1) * 8) & 0xff;
//    }
//    return out;
//}

