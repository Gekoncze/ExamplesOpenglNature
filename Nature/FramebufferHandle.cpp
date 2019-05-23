#include "FramebufferHandle.h"

using namespace cz_mg_opengl;

FramebufferHandle::FramebufferHandle()
{
	glGenFramebuffers(1, &handle);
	Opengl::checkError("Could not create frame bufer.");
}

FramebufferHandle::~FramebufferHandle()
{
	glDeleteFramebuffers(1, &handle);
}
