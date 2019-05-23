#include "ProgramHandle.h"

using namespace cz_mg_opengl;

ProgramHandle::ProgramHandle()
{
	handle = glCreateProgram();
	Opengl::checkError("Could not create framebufer.");
}

ProgramHandle::~ProgramHandle()
{
	glDeleteProgram(handle);
}
