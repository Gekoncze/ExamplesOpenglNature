#include "RenderBufferHandle.h"

using namespace cz_mg_opengl;

RenderbufferHandle::RenderbufferHandle()
{
	glGenRenderbuffers(1, &handle);
	Opengl::checkError("Could not create render buffer.");
}

RenderbufferHandle::~RenderbufferHandle()
{
	glDeleteRenderbuffers(1, &handle);
}
