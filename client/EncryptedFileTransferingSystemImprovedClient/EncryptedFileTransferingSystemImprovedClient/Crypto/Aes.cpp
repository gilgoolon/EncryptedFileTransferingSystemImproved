#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>

#include "Aes.hpp"
#include "../Common/Logging/Logger.hpp"

buffer::Buffer crypto::aes::encrypt(const buffer::Buffer& data, const buffer::Buffer& aes_key)
{
    if (aes_key.size() != DEFAULT_AES_KEY_SIZE) {
        throw std::runtime_error("invalid AES key length");
    }

    buffer::Byte iv[CryptoPP::AES::BLOCKSIZE] = { IV_UNINITIALIZED_VALUE };
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
    e.SetKeyWithIV(aes_key.data(), aes_key.size(), iv);

    std::string plaintext(data.begin(), data.end());
    std::string ciphertext;
    CryptoPP::StringSource ss(plaintext, true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(ciphertext)));

    return buffer::Buffer(ciphertext.begin(), ciphertext.end());
}