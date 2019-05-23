#include "Framebuffer.h"
#include "StringUtilities.h"

using namespace cz_mg_opengl;

Framebuffer::Framebuffer(int width, int height) : texture(width, height, GL_LINEAR, GL_LINEAR)
{
	if (width < 1) width = 1;
	if (height < 1) height = 1;

	this->width = width;
	this->height = height;

	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer.getHandle());
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	Opengl::checkError("Could not setup render buffer.");

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.getHandle());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.getHandle());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getTexture().getHandle(), 0);
	Opengl::checkError("Could not setupframe buffer.");

	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw OpenglException("Could not create framebuffer: " + Opengl::frameBufferErrorToString(status));
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer()
{
}

Texture& Framebuffer::getTexture()
{
	return texture;
}

void Framebuffer::use()
{
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFramebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.getHandle());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Opengl::checkError("Could not use frame buffer.");
}

void Framebuffer::unuse()
{
	glBindFramebuffer(GL_FRAMEBUFFER, oldFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Opengl::checkError(std::string("Could not use old frame buffer ") + oldFramebuffer);
}
