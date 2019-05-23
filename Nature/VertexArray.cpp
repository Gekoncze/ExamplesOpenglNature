#include "VertexArray.h"
#include "StringUtilities.h"

using namespace cz_mg_opengl;

VertexArray::VertexArray()
{
}

VertexArray::~VertexArray()
{
}

void VertexArray::bind()
{
	glBindVertexArray(vertexArray.getHandle());
	Opengl::checkError("Could not bind vertex array.");
}

void VertexArray::setAttribute(int location, FloatBuffer& buffer)
{
	glEnableVertexAttribArray(location);
	Opengl::checkError(std::string("Could not enable attribute ") + location + ".");

	glBindBuffer(GL_ARRAY_BUFFER, buffer.getBuffer().getHandle());
	Opengl::checkError(std::string("Could not bind buffer for attribute ") + location + ".");

	glVertexAttribPointer(location, buffer.getN(), GL_FLOAT, GL_FALSE, 0, 0);
	Opengl::checkError(std::string("Could not set attribute pointer ") + location + ".");
}

void VertexArray::setAttributeInstance(int location, FloatBuffer& buffer, int divisor)
{
	glEnableVertexAttribArray(location);
	Opengl::checkError(std::string("Could not enable attribute ") + location + ".");

	glBindBuffer(GL_ARRAY_BUFFER, buffer.getBuffer().getHandle());
	Opengl::checkError(std::string("Could not bind buffer for attribute ") + location + ".");

	glVertexAttribPointer(location, buffer.getN(), GL_FLOAT, GL_FALSE, 0, 0);
	Opengl::checkError(std::string("Could not set attribute pointer ") + location + ".");

	glVertexAttribDivisor(location, divisor);
	Opengl::checkError(std::string("Could not set attribute divisor ") + location + ".");
}