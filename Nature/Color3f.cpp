#include "Color3f.h"

Color3f::Color3f(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color3f::Color3f()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

Color3f::~Color3f()
{
}

Color3f Color3f::mix(Color3f a, Color3f b, float m1)
{
	float m2 = 1 - m1;
	return Color3f(
		a.r * m1 + b.r * m2,
		a.g * m1 + b.g * m2,
		a.b * m1 + b.b * m2
	);
}

float* Color3f::createArray(std::vector<Color3f> colors)
{
	float* array = new float[colors.size() * 3];
	for (int i = 0; i < colors.size(); i++)
	{
		array[i * 3 + 0] = colors[i].r;
		array[i * 3 + 1] = colors[i].g;
		array[i * 3 + 2] = colors[i].b;
	}
	return array;
}
