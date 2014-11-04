#include "stdafx.h"
#include "Triangle.h"
#include "Context.h"


Triangle::Triangle(float v1[3], float v2[3], float v3[3])
{
	vertexes[0][0] = v1[0];
	vertexes[0][1] = v1[1];
	vertexes[0][2] = v1[2];
	vertexes[1][0] = v2[0];
	vertexes[1][1] = v2[1];
	vertexes[1][2] = v2[2];
	vertexes[2][0] = v3[0];
	vertexes[2][1] = v3[1];
	vertexes[2][2] = v3[2];
}

void Triangle::render(Context* context)
{
	context->setColor();
	context->drawVertex(vertexes[0]);
	context->drawVertex(vertexes[1]);
	context->drawVertex(vertexes[2]);
}

Triangle::~Triangle()
{
}
