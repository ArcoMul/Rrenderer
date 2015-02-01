#include "Vector3.h"

Rr::Vector3::Vector3(float x, float y, float z)
{
	this->points[0] = x;
	this->points[1] = y;
	this->points[2] = z;
}

Rr::Vector3::~Vector3()
{
}
