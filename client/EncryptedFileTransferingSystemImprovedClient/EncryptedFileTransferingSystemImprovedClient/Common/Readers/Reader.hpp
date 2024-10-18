#pragma once
#include <string>

#include "../Buffer.hpp"
using buffer::Buffer;

class IReader {
public:
    virtual ~IReader() = default;

    virtual Buffer read(const size_t length) = 0;
};
