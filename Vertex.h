#pragma once
class Vertex
{
public:
	Vertex(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	~Vertex();
private:
	float x;
	float y;
	float z;
};

