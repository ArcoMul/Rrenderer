#include "Matrix4.h"

#include <cstdio>

Rr::Matrix4::Matrix4()
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

Rr::Matrix4::~Matrix4()
{
}

void Rr::Matrix4::print()
{
	printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n", points[0], points[1], points[2], points[3], points[4], points[5], points[6], points[7], points[8], points[9], points[10], points[11], points[12], points[13], points[14], points[15]);
}