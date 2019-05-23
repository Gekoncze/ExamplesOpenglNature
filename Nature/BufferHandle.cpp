#include "BufferHandle.h"

using namespace cz_mg_opengl;

BufferHandle::BufferHandle()
{
	glGenBuffers(1, &handle);
	Opengl::checkError("Could not create buffer.");
}

BufferHandle::~BufferHandle()
{
	glDeleteBuffers(1, &handle);
}
