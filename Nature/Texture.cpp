#include "Texture.h"

using namespace cz_mg_opengl;

Texture::Texture(int width, int height, int min_filter, int mag_filter)
{
	if (width < 1) width = 1;
	if (height < 1) height = 1;
	glBindTexture(GL_TEXTURE_2D, texture.getHandle());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	Opengl::checkError("Could not create texture.");
}

Texture::Texture(int width, int height, std::vector<GLubyte>& data, bool mipmap)
{
	if (width < 1) width = 1;
	if (height < 1) height = 1;
	glBindTexture(GL_TEXTURE_2D, texture.getHandle());
	if (mipmap) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Opengl::checkError("Could set texture options.");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	Opengl::checkError("Could not copy texture to opengl.");

	if (mipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		Opengl::checkError("Could not create mipmaps.");
	}
}

Texture::~Texture()
{
}

TextureHandle& Texture::getTexture()
{
	return texture;
}
