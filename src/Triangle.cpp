#include "Triangle.h"
#include "Context.h"

Triangle::Triangle(float v1[3], float v2[3], float v3[3])
{
	vertexes[0] = v1[0];
	vertexes[1] = v1[1];
	vertexes[2] = v1[2];
	vertexes[3] = v2[0];
	vertexes[4] = v2[1];
	vertexes[5] = v2[2];
	vertexes[6] = v3[0];
	vertexes[7] = v3[1];
	vertexes[8] = v3[2];
}

float* Triangle::getVertexes()
{
	return vertexes;
}

Triangle::~Triangle()
{
}
