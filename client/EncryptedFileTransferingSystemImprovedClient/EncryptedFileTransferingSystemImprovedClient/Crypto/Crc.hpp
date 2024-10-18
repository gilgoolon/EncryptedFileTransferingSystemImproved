#include <cstdint>

#include "../Common/Buffer.hpp"

namespace crypto {
	namespace crc {
		uint32_t calculate(const buffer::Buffer& data);
	};
};
