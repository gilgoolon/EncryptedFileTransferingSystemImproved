#include <iostream>

#include "ConsoleWriter.hpp"
using buffer::Buffer;

void ConsoleWriter::write(const Buffer& data)
{
    std::cout << buffer::to_string(data) << std::endl;
}
