#include "IOException.h"

IOException::IOException(std::string message) : std::exception(message.c_str())
{
}

IOException::~IOException()
{
}
