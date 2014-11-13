#include "Mesh.h"
#include "Renderer.h"
#include "VideoDriver.h"
#include <GLFW/glfw3.h>
#include "Triangle.h"

Mesh::Mesh()
{
}

void Mesh::setPoints(std::vector<float> points)
{
	this->points = points;
	Rr::Renderer::instance()->video->bufferVertexes(&vbo, &vao, points.size(), &points[0]);
}

GLuint Mesh::getVAO()
{
	return this->vao;
}

int Mesh::getPointCount()
{
	return points.size();
}

Mesh::~Mesh()
{
}
