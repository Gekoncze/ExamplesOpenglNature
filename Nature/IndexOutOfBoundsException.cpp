#include "IndexOutOfBoundsException.h"

IndexOutOfBoundsException::IndexOutOfBoundsException(std::string message) : std::exception(message.c_str())
{
}

IndexOutOfBoundsException::~IndexOutOfBoundsException()
{
}
