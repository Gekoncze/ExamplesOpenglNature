#pragma once
#include <exception>
#include <string>

class IndexOutOfBoundsException : public std::exception
{
public:
	IndexOutOfBoundsException(std::string message);
	~IndexOutOfBoundsException();
};

