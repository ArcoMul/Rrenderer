#pragma once

class GLFWwindow;
class Vertex;
class Triangle;

class Context
{
public:
	Context();
	void render(GLFWwindow* window);
	void Context::addTriangle(Triangle* triangle);
	void setColor();
	void drawVertex(Vertex* vertex);
	~Context();
private:
	int triangle_count;
	Triangle* triangles [2];
};

