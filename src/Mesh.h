#pragma once

#include "Rrenderer.h"
#include <GL/glew.h>
#include <vector>
#include "Triangle.h"

class RRENDERER_API Mesh
{
public:
	Mesh();
	void setPoints(std::vector<float> points);
	int getPointCount();
	GLuint getVAO();
	~Mesh();
private:
	GLuint vbo;
	GLuint vao;
	std::vector<float> points;
};

