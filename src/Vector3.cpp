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

Rr::Vector3 Rr::Vector3::operator+ (Rr::Vector3 other)
{
	return Rr::Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Rr::Vector3::~Vector3()
{
}
