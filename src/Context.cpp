#include "Renderer.h"
#include "Context.h"
#include "VideoDriver.h"

Context::Context()
{
	video = Rr::Renderer::instance()->video;
}

void Context::render()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		video->renderMesh(&meshes[i]);
	}
}

void Context::addMesh(Mesh mesh)
{
	meshes.push_back(mesh);
}

Context::~Context()
{
}
