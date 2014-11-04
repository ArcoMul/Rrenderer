#include "stdafx.h"
#include "Mesh.h"
#include "Triangle.h"

Mesh::Mesh()
{
}

void Mesh::addTriangle(Triangle triangle)
{
	triangles.push_back(triangle);
}

void Mesh::render(Context* context)
{
	for (int i = 0; i < triangles.size(); i++)
	{
		triangles[i].render(context);
	}
}

Mesh::~Mesh()
{
}
