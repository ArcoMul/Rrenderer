#pragma once

#include "Rrenderer.h"

class Context;

class RRENDERER_API Triangle
{
public:
	Triangle(float v1[3], float v2[3], float v3[3]);
	float* getVertexes();
	~Triangle();
private:
	float vertexes[9];
};

