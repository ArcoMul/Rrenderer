#pragma once

#include "Rrenderer.h"
#include <vector>
#include "Mesh.h"

struct GLFWwindow;
class Triangle;

class RRENDERER_API Context
{
public:
	Context();
	void render(GLFWwindow* window);
	void addMesh(Mesh mesh);
	void setColor();
	void drawVertex(float vertex[3]);
	~Context();
private:
	std::vector<Mesh> meshes;
};

