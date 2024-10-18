#include <sstream>

#include "StringUtils.hpp"

std::vector<std::string> string_utils::split(const std::string& string, const char delimiter, const size_t max)
{
    std::stringstream ss(string + delimiter);
    std::string segment;
    std::vector<std::string> seglist;

    for (size_t i = 0; i < max && std::getline(ss, segment, delimiter); i++) {
        seglist.push_back(segment);
    }

    std::getline(ss, segment, '\0');
    if (!segment.empty()) {
        seglist.push_back(segment.substr(0, segment.length() - 1));
    }
    return seglist;
}

std::string string_utils::extend(const std::string& str, const size_t new_length)
{
    std::string working_string = str;
    working_string.resize(new_length);
    return working_string;
}
