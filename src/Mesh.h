#pragma once

#include "Rrenderer.h"
#include <vector>
#include "Triangle.h"

class Context;

class RRENDERER_API Mesh
{
public:
	Mesh();
	void addTriangle(Triangle triangle);
	std::vector<Triangle>* getTriangles();
	~Mesh();
private:
	std::vector<Triangle> triangles;
};

