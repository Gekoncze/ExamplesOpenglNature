#include "Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

int Renderer::getWidth()
{
	return width;
}

int Renderer::getHeight()
{
	return height;
}

float Renderer::getAspect()
{
	return ((float)width) / height;
}

void Renderer::setSize(int width, int height)
{
	if (width < 1) width = 1;
	if (height < 1) height = 1;
	this->width = width;
	this->height = height;
}
