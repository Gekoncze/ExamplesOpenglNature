#include "OpenGL.h"
#include "OpenglException.h"
#include "StringUtilities.h"

using namespace cz_mg_opengl;

void Opengl::checkError(std::string message)
{
	int error = glGetError();
	if (error != GL_NO_ERROR) throw OpenglException(message + " " + errorToString(error));
}

std::string Opengl::errorToString(GLenum error)
{
	switch (error)
	{
		case GL_NO_ERROR:          return "";
		case GL_INVALID_ENUM:      return "INVALID ENUM";
		case GL_INVALID_VALUE:     return "INVALID VALUE";
		case GL_INVALID_OPERATION: return "INVALID OPERATION";
		case GL_OUT_OF_MEMORY:     return "OUT OF MEMORY";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "INVALID FRAMEBUFFER OPERATION";
		case 0x0503: return "STACK OVERFLOW";
		case 0x0504: return "STACK UNDERFLOW";
		case 0x0507: return "CONTEXT LOST";
		default: return std::string("UNKNOWN OPENGL ERROR ") + error;
	}
}


std::string Opengl::frameBufferErrorToString(GLenum error)
{
	switch (error)
	{
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: return "GL FRAMEBUFFER INCOMPLETE ATTACHMENT";
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "GL FRAMEBUFFER INCOMPLETE MISSING ATTACHMENT";
		//case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS: return "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS";
		case GL_FRAMEBUFFER_UNSUPPORTED: return "GL FRAMEBUFFER UNSUPPORTED";
		default: return std::string("UNKNOWN FRAMEBUFFER ERROR ") + error;
	}
}
