#include "../Common/Buffer.hpp"

namespace crypto {
	namespace aes {
        static constexpr uint8_t IV_UNINITIALIZED_VALUE = 0x00;
        static constexpr size_t DEFAULT_AES_KEY_SIZE = 8;

        buffer::Buffer encrypt(const buffer::Buffer& data, const buffer::Buffer& aes_key);
	};
};
