#include "../Common/Buffer.hpp"

class ISerializable {
public:
	virtual ~ISerializable() = default;

	virtual buffer::Buffer serialize() const = 0;
};


buffer::Buffer serialize_uint8(const uint8_t data);

buffer::Buffer serialize_uint16(const uint16_t data);

buffer::Buffer serialize_uint32(const uint32_t data);

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