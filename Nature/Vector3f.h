#pragma once
#include <vector>

class Vector3f
{
public:
	float x;
	float y;
	float z;

public:
	Vector3f(float x, float y, float z);
	Vector3f();
	~Vector3f();

	static Vector3f minus(Vector3f p1, Vector3f p2);
	static Vector3f cross(Vector3f p1, Vector3f p2);
	static float dotProduct(Vector3f p1, Vector3f p2);

	static float* createArray(std::vector<Vector3f> vectors);
};

