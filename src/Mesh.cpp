#include "Mesh.h"
#include "Triangle.h"

Mesh::Mesh()
{
}

void Mesh::addTriangle(Triangle triangle)
{
	triangles.push_back(triangle);
}

std::vector<Triangle>* Mesh::getTriangles()
{
	return &triangles;
}

Mesh::~Mesh()
{
}
