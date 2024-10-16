#pragma once
#include <vector>
#include <string>


namespace string_utils {
	static const size_t SPLIT_ONCE = 1;

	std::vector<std::string> split(const std::string& string, const char delimiter, const size_t max);
};