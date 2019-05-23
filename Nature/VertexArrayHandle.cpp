#include "VertexArrayHandle.h"

using namespace cz_mg_opengl;

VertexArrayHandle::VertexArrayHandle()
{
	glGenVertexArrays(1, &handle);
	Opengl::checkError("Could not create vertex array.");
}

VertexArrayHandle::~VertexArrayHandle()
{
	glDeleteVertexArrays(1, &handle);
}
