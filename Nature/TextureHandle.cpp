#include "TextureHandle.h"

using namespace cz_mg_opengl;

TextureHandle::TextureHandle()
{
	glGenTextures(1, &handle);
	Opengl::checkError("Could not create texture.");
}

TextureHandle::~TextureHandle()
{
	glDeleteTextures(1, &handle);
}
