#pragma once

#include <exception>
#include <string>

class IOException : public std::exception
{
public:
	IOException(std::string message);
	~IOException();
};

