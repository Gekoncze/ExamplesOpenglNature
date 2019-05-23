#include "GrassClump.h"

GrassClump::GrassClump(Vector3f position, Color3f color, float size, float pliability) : position(position), color(color)
{
	this->size = size;
	this->pliability = pliability;
}

GrassClump::GrassClump() : position(), color()
{
	this->size = 0;
	this->pliability = 0;
}

GrassClump::~GrassClump()
{
}
