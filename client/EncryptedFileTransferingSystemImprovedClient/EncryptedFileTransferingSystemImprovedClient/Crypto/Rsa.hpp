#include <string>

#include "../Common/Buffer.hpp"

namespace crypto {
	namespace rsa {

	static constexpr size_t DEFAULT_RSA_KEY_SIZE = 1024;

	void generate_key_pair(buffer::Buffer& private_key_dest, buffer::Buffer& public_key_dest);

	buffer::Buffer decrypt(const buffer::Buffer& data, const buffer::Buffer& private_key_data);
	};
};
