#include "FragmentShaderHandle.h"

using namespace cz_mg_opengl;

FragmentShaderHandle::FragmentShaderHandle()
{
	handle = glCreateShader(GL_FRAGMENT_SHADER);
	Opengl::checkError("Could not create fragment shader.");
}

FragmentShaderHandle::~FragmentShaderHandle()
{
	glDeleteShader(handle);
}
