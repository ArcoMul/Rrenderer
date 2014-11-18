#include "Renderer.h"
#include "Context.h"
#include "VideoDriver.h"

Rr::Context::Context()
{
	video = Rr::Renderer::instance()->video;
}

void Rr::Context::render()
{
	for (int i = 0; i < objects.size(); i++)
	{
		video->renderObject(&objects[i]);
	}
}

void Rr::Context::addObject(Object object)
{
	objects.push_back(object);
}

Rr::Context::~Context()
{
}
