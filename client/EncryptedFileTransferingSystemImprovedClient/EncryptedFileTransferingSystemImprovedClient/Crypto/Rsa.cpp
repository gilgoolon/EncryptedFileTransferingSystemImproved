#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

#include "Rsa.hpp"
#include "../Common/Buffer.hpp"

static CryptoPP::AutoSeededRandomPool rng;

void crypto::rsa::generate_key_pair(buffer::Buffer& private_key_dest, buffer::Buffer& public_key_dest)
{
    CryptoPP::RSA::PrivateKey private_key;
    private_key.GenerateRandomWithKeySize(rng, DEFAULT_RSA_KEY_SIZE);
    CryptoPP::RSA::PublicKey public_key(private_key);

    std::string private_key_str;
    CryptoPP::StringSink private_key_sink(private_key_str);
    private_key.DEREncode(private_key_sink);
    private_key_dest = buffer::Buffer(private_key_str.begin(), private_key_str.end());

    std::string public_key_str;
    CryptoPP::StringSink public_key_sink(public_key_str);
    public_key.DEREncode(public_key_sink);
    public_key_dest = buffer::Buffer(public_key_str.begin(), public_key_str.end());
}

buffer::Buffer crypto::rsa::decrypt(const buffer::Buffer& data, const buffer::Buffer& private_key_data)
{
    std::string private_key_str(private_key_data.begin(), private_key_data.end());

    CryptoPP::RSA::PrivateKey private_key;
    CryptoPP::StringSource ss_private_key(private_key_str, true);
    private_key.Load(ss_private_key);

    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(private_key);

    std::string decrypted_data;
    CryptoPP::StringSource ss_encrypted_data(reinterpret_cast<const buffer::Byte*>(data.data()), data.size(), true,
        new CryptoPP::PK_DecryptorFilter(rng, decryptor,
            new CryptoPP::StringSink(decrypted_data)
        )
    );

    return buffer::Buffer(decrypted_data.begin(), decrypted_data.end());
}
