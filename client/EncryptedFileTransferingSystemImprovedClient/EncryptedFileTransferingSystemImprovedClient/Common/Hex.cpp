#include <sstream>
#include <iomanip>

#include "Hex.hpp"

std::string hex::encode(const buffer::Buffer& data)
{
    std::ostringstream oss;
    for (auto byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}

buffer::Buffer hex::decode(const std::string& str)
{
    buffer::Buffer data;
    size_t len = str.length();
    for (size_t i = 0; i < len; i += 2) {
        std::string byteString = str.substr(i, 2);
        buffer::Byte byte = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
        data.push_back(byte);
    }
    return data;
}
