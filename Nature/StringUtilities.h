#pragma once

#include <string>

inline std::string operator+(std::string left, int right)
{
	return left.append(std::to_string(right));
}

inline std::string operator+(int left, std::string right)
{
	return right.insert(0, std::to_string(left));
}