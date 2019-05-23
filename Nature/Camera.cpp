#include "Camera.h"

Camera::Camera()
{
	yaw = 0;
	pitch = 0;
	roll = 0;
	distance = 0;
	x = 0;
	y = 0;
	z = 0;
}

Camera::~Camera()
{
}

Matrix4f Camera::getMatrix() {
	return Matrix4f::multiply(
		Matrix4f::translation(0, 0, distance),
		Matrix4f::yawPitchRoll(yaw, pitch, roll),
		Matrix4f::translation(-x, -y, -z)
	);
}
