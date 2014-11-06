#pragma once

#include "Rrenderer.h"

class GLFWwindow;
class Mesh;

class RRENDERER_API VideoDriver
{
public:
	VideoDriver();
	~VideoDriver();

	bool init();
	bool createWindow(int x, int y, char* title);
	GLFWwindow* getWindow();
	double getTime();
	bool windowShouldClose();

	void prepareFrame();
	void finishFrame();
	void renderMesh(Mesh* mesh);
	void setColor();
	void drawVertex(float* vertex);
private:
	GLFWwindow* window;
};

