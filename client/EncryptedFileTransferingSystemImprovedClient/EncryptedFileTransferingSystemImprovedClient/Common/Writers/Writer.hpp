#pragma once
#include <string>

#include "../Buffer.hpp"

class IWriter {
public:
    virtual ~IWriter() = default;

    virtual void write(const buffer::Buffer& data) = 0;
};
