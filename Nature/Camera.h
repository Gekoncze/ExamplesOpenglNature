#pragma once
#include "Matrix4f.h"

class Camera
{
public:
	float yaw, pitch, roll;
	float distance;
	float x, y, z;

	Camera();
	~Camera();
	Matrix4f getMatrix();
};

