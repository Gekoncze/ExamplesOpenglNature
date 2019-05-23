#include "FloatBuffer.h"

using namespace cz_mg_opengl;

FloatBuffer::FloatBuffer(float* data, int n, int count)
{
	setData(data, n, count, GL_STATIC_DRAW);
}

FloatBuffer::FloatBuffer()
{
}

FloatBuffer::~FloatBuffer()
{
}

BufferHandle& FloatBuffer::getBuffer()
{
	return buffer;
}

int FloatBuffer::getN()
{
	return n;
}

void FloatBuffer::setDataStatic(float* data, int n, int count)
{
	setData(data, n, count, GL_STATIC_DRAW);
}

void FloatBuffer::setDataStream(float* data, int n, int count)
{
	setData(data, n, count, GL_STREAM_DRAW);
}

void FloatBuffer::setData(float* data, int n, int count, int usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer.getHandle());
	Opengl::checkError("Could not bind buffer.");
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, usage);
	Opengl::checkError("Could not move data to buffer.");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	this->n = n;
	this->count = count;
}