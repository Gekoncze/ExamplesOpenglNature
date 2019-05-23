#include "OpenglException.h"

using namespace cz_mg_opengl;

OpenglException::OpenglException(std::string message) : std::exception()
{
	this->message = message;
}

OpenglException::~OpenglException()
{
}

std::string OpenglException::getMessage()
{
	return message;
}
