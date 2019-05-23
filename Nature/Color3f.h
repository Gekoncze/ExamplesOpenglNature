#pragma once
#include <vector>

class Color3f
{
public:
	float r;
	float g;
	float b;

public:
	Color3f(float r, float g, float b);
	Color3f();
	~Color3f();

	static Color3f mix(Color3f a, Color3f b, float m1);
	static float* createArray(std::vector<Color3f> colors);
};

