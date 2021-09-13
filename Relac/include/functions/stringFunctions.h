#pragma once
#include <string>

inline std::string mid(const std::string& base, size_t index, size_t size)
{
	return std::string(base.begin() + index, base.begin() + index + size);
}