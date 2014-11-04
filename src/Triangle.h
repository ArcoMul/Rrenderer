#pragma once

#include "Rrenderer.h"

class Context;

class RRENDERER_API Triangle
{
public:
	Triangle(float v1[3], float v2[3], float v3[3]);
	void render(Context* context);
	~Triangle();
private:
	float vertexes[3][3];
};

