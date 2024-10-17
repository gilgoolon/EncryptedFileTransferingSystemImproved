#include <cryptopp/crc.h>
#include <cryptopp/crc.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

#include "Crc.hpp"
#include "../Common/Logging/Logger.hpp"

uint32_t crypto::crc::calculate(const buffer::Buffer& data)
{
    CryptoPP::CRC32 crc;
    uint32_t checksum = 0;
    crc.Update(data.data(), data.size());
    crc.TruncatedFinal(reinterpret_cast<buffer::Byte*>(&checksum), sizeof(checksum));
    return checksum;
}
