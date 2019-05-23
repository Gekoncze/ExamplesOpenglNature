#include "Vector3f.h"

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::Vector3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3f::~Vector3f()
{
}

Vector3f Vector3f::minus(Vector3f p1, Vector3f p2)
{
	return Vector3f(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

Vector3f Vector3f::cross(Vector3f p1, Vector3f p2)
{
	return Vector3f(
		p1.y * p2.z - p1.z * p2.y,
		p1.z * p2.x - p1.x * p2.z,
		p1.x * p2.y - p1.y * p2.x
	);
}

float Vector3f::dotProduct(Vector3f p1, Vector3f p2)
{
	return p1.x* p2.x + p1.y * p2.y + p1.z * p2.z;
}

float* Vector3f::createArray(std::vector<Vector3f> vectors)
{
	float* array = new float[vectors.size() * 3];
	for (int i = 0; i < vectors.size(); i++)
	{
		array[i * 3 + 0] = vectors[i].x;
		array[i * 3 + 1] = vectors[i].y;
		array[i * 3 + 2] = vectors[i].z;
	}
	return array;
}
