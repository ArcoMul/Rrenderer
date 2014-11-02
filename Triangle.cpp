#include "stdafx.h"
#include "Triangle.h"
#include "Context.h"


Triangle::Triangle(Vertex* v1, Vertex* v2, Vertex* v3)
{
	vertexes[0] = v1;
	vertexes[1] = v2;
	vertexes[2] = v3;
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
