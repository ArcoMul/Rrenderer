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
	this->position = vector;
	this->recalculateViewMatrix();
}

Rr::Vector3 Rr::Camera::getPosition()
{
	return this->position;
}

void Rr::Camera::setRotation(Rr::Vector3 vector)
{
	this->rotation = vector;
	this->recalculateViewMatrix();
}

Rr::Vector3 Rr::Camera::getRotation()
{
	return this->rotation;
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

void Rr::Camera::translate(Rr::Vector3 vector)
{
	Matrix4 translationMatrix;
	translationMatrix.translate(vector);
	viewMatrix = translationMatrix * viewMatrix;
}

void Rr::Camera::rotate(Rr::Vector3 vector)
{
	Matrix4 rotationXMatrix;
	rotationXMatrix.rotateX(vector.x);

	Matrix4 rotationYMatrix;
	rotationYMatrix.rotateY(vector.y);

	Matrix4 rotationZMatrix;
	rotationZMatrix.rotateZ(vector.z);

	viewMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix * viewMatrix;
}

void Rr::Camera::recalculateViewMatrix()
{
	viewMatrix.toIdentity();
	
	Matrix4 translationMatrix;
	translationMatrix.translate(this->position);

	Matrix4 rotationXMatrix;
	rotationXMatrix.rotateX(this->rotation.x);

	Matrix4 rotationYMatrix;
	rotationYMatrix.rotateY(this->rotation.y);

	Matrix4 rotationZMatrix;
	rotationZMatrix.rotateZ(this->rotation.z);

	viewMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;
}

void Rr::Camera::recalculateProjectMatrix()
{
	float top = this->near * tan((M_PI / 180.0) * (this->FOV / 2.0));
	float bottom = -top;
	float right = top * this->aspect;
	float left = -right;

	this->projectionMatrix[0] = (2.0 * this->near) / (right - left);
	this->projectionMatrix[2] = (right + left) / (right - left);
	this->projectionMatrix[5] = (2.0 * this->near) / (top - bottom);
	this->projectionMatrix[6] = (top + bottom) / (top - bottom);
	this->projectionMatrix[10] = -(far + near) / (far - near);
	this->projectionMatrix[11] = -(2.0 * far * near) / (far - near);
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