#pragma once

#include "Rrenderer.h"
#include <vector>
#include "Mesh.h"

class VideoDriver;

class RRENDERER_API Context
{
public:
	Context();
	void render();
	void addMesh(Mesh mesh);
	void setColor();
	void drawVertex(float vertex[3]);
	~Context();
private:
	VideoDriver* video;
	std::vector<Mesh> meshes;
};

