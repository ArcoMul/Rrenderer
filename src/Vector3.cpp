#include "Vector3.h"

Rr::Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Rr::Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Rr::Vector3::~Vector3()
{
}
