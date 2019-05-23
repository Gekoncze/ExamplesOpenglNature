#include "VertexShaderHandle.h"

using namespace cz_mg_opengl;

VertexShaderHandle::VertexShaderHandle()
{
	handle = glCreateShader(GL_VERTEX_SHADER);
	Opengl::checkError("Could not create vertex shader.");
}

VertexShaderHandle::~VertexShaderHandle()
{
	glDeleteShader(handle);
}
