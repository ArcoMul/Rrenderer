#include "Mesh.h"
#include "Renderer.h"
#include "VideoDriver.h"
#include <GLFW/glfw3.h>

Rr::Mesh::Mesh()
{
	Rr::Renderer::instance()->video->generateVertexArray(&this->vao);
}

void Rr::Mesh::setPoints(std::vector<float> points)
{
	this->points = points;
	Rr::Renderer::instance()->video->bufferVertexes(&vbo, &vao, points.size(), &points[0]);
}

void Rr::Mesh::setNormals(std::vector<float> normals)
{
	this->normals = normals;
	Rr::Renderer::instance()->video->bufferNormals(&nbo, &vao, normals.size(), &normals[0]);
}

int Rr::Mesh::getPointCount()
{
	return points.size();
}

Rr::Mesh::~Mesh()
{

}
