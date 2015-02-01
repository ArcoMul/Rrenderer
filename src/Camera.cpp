#include "Camera.h"

Rr::Camera::Camera()
{
}

Rr::Camera::~Camera()
{
}

void Rr::Camera::setPosition(Rr::Vector3 vector)
{
	viewMatrix[3] = vector.x();
	viewMatrix[7] = vector.y();
	viewMatrix[11] = vector.z();
}

Rr::Matrix4* Rr::Camera::getViewMatrix()
{
	return &viewMatrix;
}