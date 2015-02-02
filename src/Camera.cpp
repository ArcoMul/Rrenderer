#include "Camera.h"
#include <math.h>
#include <cstdio>

Rr::Camera::Camera()
{
	this->near = 0.1;
	this->far = 10.0;
	this->aspect = 4.0 / 3.0;
	this->FOV = 35.0;
	this->recalculateProjectMatrix();
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

void Rr::Camera::setNear(float n)
{
	this->near = n;
	this->recalculateProjectMatrix();
}

void Rr::Camera::setFar(float n)
{
	this->far = n;
	this->recalculateProjectMatrix();
}

void Rr::Camera::setAspect(float n)
{
	this->aspect = n;
	this->recalculateProjectMatrix();
}

void Rr::Camera::setFOV(float angle)
{
	this->FOV = angle;
	this->recalculateProjectMatrix();
}

void Rr::Camera::recalculateProjectMatrix()
{
	float top = this->near * tan((M_PI / 180) * (this->FOV / 2));
	float bottom = -top;
	float right = top * this->aspect;
	float left = -right;

	this->projectionMatrix[0] = (2 * this->near) / (right - left);
	this->projectionMatrix[3] = (right + left) / (right - left);
	this->projectionMatrix[5] = (2 * this->near) / (top - bottom);
	this->projectionMatrix[6] = (top + bottom) / (top - bottom);
	this->projectionMatrix[10] = (far + near) / (far - near);
	this->projectionMatrix[11] = (2 * far * near) / (far - near);
	this->projectionMatrix[14] = -1;
}

Rr::Matrix4* Rr::Camera::getViewMatrix()
{
	return &viewMatrix;
}

Rr::Matrix4* Rr::Camera::getProjectionMatrix()
{
	return &projectionMatrix;
}