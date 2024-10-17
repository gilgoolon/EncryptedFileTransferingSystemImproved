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

void os_utils::write_text_file(const std::filesystem::path& path, const std::string& text)
{
    std::ofstream out_file(path, std::ios::out | std::ios::trunc);
    if (!out_file.is_open()) {
        throw std::runtime_error("failed to open the file: " + path.string());
    }
    out_file << text;
    if (!out_file.good()) {
        throw std::runtime_error("failed to write to the file: " + path.string());
    }
}
