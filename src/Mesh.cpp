#include "Mesh.h"
#include "Renderer.h"
#include "VideoDriver.h"
#include <GLFW/glfw3.h>

Rr::Mesh::Mesh()
{
	vbo = 0;
	nbo = 0;
	vao = 0;
	printf("Create mesh\n");
}

void Rr::Mesh::setPoints(std::vector<float> points)
{
	this->points = points;
	Rr::Renderer::instance()->video->generateVertexArray(&this->vao);
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

void Rr::Mesh::deleteBuffers()
{
	if (vbo != 0) {
		printf("Delete vbo\n");
		Rr::Renderer::instance()->video->deleteBuffer(&vbo);
	}
	if (nbo != 0) {
		printf("Delete nbo\n");
		Rr::Renderer::instance()->video->deleteBuffer(&nbo);
	}
	if (vao != 0) {
		printf("Delete vao\n");
		Rr::Renderer::instance()->video->deleteBuffer(&vao);
	}
}

Rr::Mesh::~Mesh()
{

}
