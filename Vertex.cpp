#include "stdafx.h"
#include "Vertex.h"


Vertex::Vertex(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vertex::getX()
{
	return x;
}

float Vertex::getY()
{
	return y;
}

float Vertex::getZ()
{
	return z;
}

Vertex::~Vertex()
{
}
