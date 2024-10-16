#pragma once
#include "Buffer.hpp"

namespace hex {
    std::string encode(const buffer::Buffer& data);

    buffer::Buffer decode(const std::string& str);
};
