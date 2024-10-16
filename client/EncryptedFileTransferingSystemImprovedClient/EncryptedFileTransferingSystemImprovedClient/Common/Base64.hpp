#pragma once
#include <vector>
#include <string>

#include "Buffer.hpp"

namespace base64 {
std::string encode(const buffer::Buffer& buff);

buffer::Buffer decode(const std::string& str);
};