#pragma once

class Vertex;
class Context;

class Triangle
{
public:
	Triangle(Vertex* v1, Vertex* v2, Vertex* v3);
	void render(Context* context);
	~Triangle();
private:
	Vertex* vertexes [3];
};

