#include <cryptopp/crc.h>

#include "Crc.hpp"

uint32_t crypto::crc::calculate(const buffer::Buffer& data)
{
    CryptoPP::CRC32 crc;
    crc.Update(data.data(), data.size());
    uint8_t digest[CryptoPP::CRC32::DIGESTSIZE] = { 0 };
    crc.Final(digest);

    uint32_t crc32_value = 0;
    for (int i = 0; i < CryptoPP::CRC32::DIGESTSIZE; ++i) {
        crc32_value = (crc32_value << 8) | digest[i];
    }

    return crc32_value;
}
