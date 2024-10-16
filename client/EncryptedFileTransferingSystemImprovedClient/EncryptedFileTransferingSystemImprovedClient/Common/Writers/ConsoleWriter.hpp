#pragma once
#include "Writer.hpp"

class ConsoleWriter final : public IWriter {
public:
    explicit ConsoleWriter() = default;

    void write(const buffer::Buffer& data) override;
};
