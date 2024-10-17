#include "Serializable.hpp"

buffer::Buffer serialize_uint8(const uint8_t data)
{
    buffer::Buffer out(sizeof(data));
    out.push_back(data);
    return out;
}

buffer::Buffer serialize_uint16(const uint16_t data)
{
    buffer::Buffer out(sizeof(data));
    for (size_t i = 0; i < sizeof(data); i++) {
        out.push_back(static_cast<uint8_t>((data >> (8 * i) & 0xff)));
    }
    return out;
}

buffer::Buffer serialize_uint32(const uint32_t data)
{
    buffer::Buffer out(sizeof(data));
    for (size_t i = 0; i < sizeof(data); i++) {
        out.push_back(static_cast<uint8_t>((data >> (8 * i) & 0xff)));
    }
    return out;
}
