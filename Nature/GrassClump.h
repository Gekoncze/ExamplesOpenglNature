#pragma once
#include "Color3f.h"
#include "Vector3f.h"

class GrassClump
{
public:
	Vector3f position;
	Color3f color;
	float size;
	float pliability;

public:
	GrassClump(Vector3f position, Color3f color, float size, float pliability);
	GrassClump();
	~GrassClump();
};

