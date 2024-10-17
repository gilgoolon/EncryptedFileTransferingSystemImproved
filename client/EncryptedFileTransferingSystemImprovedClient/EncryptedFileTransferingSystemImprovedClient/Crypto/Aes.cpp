#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>

#include "Aes.hpp"
#include "../Common/Logging/Logger.hpp"

buffer::Buffer crypto::aes::encrypt(const buffer::Buffer& data, const buffer::Buffer& aes_key)
{
    static constexpr size_t NUM_BITS_IN_BYTE = 8;
    if (aes_key.size() != DEFAULT_AES_KEY_SIZE) {
        throw std::runtime_error("invalid AES key length");
    }

    buffer::Byte iv[CryptoPP::AES::BLOCKSIZE]{ IV_UNINITIALIZED_VALUE };

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
    encryption.SetKeyWithIV(aes_key.data(), aes_key.size(), iv);

    buffer::Buffer ciphertext;
    ciphertext.resize(data.size() + CryptoPP::AES::BLOCKSIZE); // Add space for IV

    std::copy(iv, iv + CryptoPP::AES::BLOCKSIZE, ciphertext.begin());

    CryptoPP::ArraySink cs(&ciphertext[CryptoPP::AES::BLOCKSIZE], ciphertext.size() - CryptoPP::AES::BLOCKSIZE);

    CryptoPP::ArraySource(data.data(), data.size(), true,
        new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::Redirector(cs)));

    return ciphertext;
}