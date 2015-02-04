#include "Matrix4.h"

#include <cstdio>
#include <math.h>

Rr::Matrix4::Matrix4()
{
	this->toIdentity();
}

Rr::Matrix4::~Matrix4()
{
}

void Rr::Matrix4::toIdentity()
{
	points[0] = 1;
	points[1] = 0;
	points[2] = 0;
	points[3] = 0;

	points[4] = 0;
	points[5] = 1;
	points[6] = 0;
	points[7] = 0;

	points[8] = 0;
	points[9] = 0;
	points[10] = 1;
	points[11] = 0;

	points[12] = 0;
	points[13] = 0;
	points[14] = 0;
	points[15] = 1;
}

void Rr::Matrix4::translate(Rr::Vector3 vector)
{
	this->points[3] = vector.x;
	this->points[7] = vector.y;
	this->points[11] = vector.z;
}

void Rr::Matrix4::rotateX(float angle)
{
	this->points[5] = cos(angle * (M_PI / 180.0));
	this->points[6] = -sin(angle * (M_PI / 180.0));
	this->points[9] = sin(angle * (M_PI / 180.0));
	this->points[10] = cos(angle * (M_PI / 180.0));
}

void Rr::Matrix4::rotateY(float angle)
{
	this->points[0] = cos(angle * (M_PI / 180.0));
	this->points[2] = sin(angle * (M_PI / 180.0));
	this->points[8] = -sin(angle * (M_PI / 180.0));
	this->points[10] = cos(angle * (M_PI / 180.0));
}

void Rr::Matrix4::rotateZ(float angle)
{
	this->points[0] = cos(angle * (M_PI / 180.0));
	this->points[1] = -sin(angle * (M_PI / 180.0));
	this->points[4] = sin(angle * (M_PI / 180.0));
	this->points[5] = cos(angle * (M_PI / 180.0));
}

Rr::Matrix4 Rr::Matrix4::operator* (Rr::Matrix4 other)
{
	Rr::Matrix4 result;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			float sum = 0.0;
			for (int inner = 0; inner < 4; inner++)
			{
				sum += points[(row * 4) + inner] * other[col + (inner * 4)];
				//printf("%d * %d + ", (row * 4) + inner, col + (inner * 4));
			}
			//printf("\n");
			result[(row * 4) + col] = sum;
		}
	}
	return result;

	// 0 * 0 + 1 * 4 + 2 * 8  + 3 * 12
	// 0 * 1 + 1 * 5 + 2 * 9  + 3 * 13
	// 0 * 2 + 1 * 6 + 2 * 10 + 3 * 14
	// 0 * 3 + 1 * 7 + 2 * 11 + 3 * 15
	// 5 * 0 + 6 * 4 + 7 * 8  + 8 * 12
}

void Rr::Matrix4::print()
{
	printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", points[0], points[1], points[2], points[3], points[4], points[5], points[6], points[7], points[8], points[9], points[10], points[11], points[12], points[13], points[14], points[15]);
}