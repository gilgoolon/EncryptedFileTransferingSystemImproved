#include <sstream>
#include <fstream>

#include "OsUtils.hpp"

std::string os_utils::read_text_file(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

uint64_t os_utils::read_uint64_from_file(const std::filesystem::path& path)
{
    return std::stol(read_text_file(path));
}
