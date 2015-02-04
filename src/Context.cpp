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

void Rr::Context::setCamera(Camera* camera)
{
	this->camera = camera;
	video->setActiveCamera(this->camera);
}

Rr::Context::~Context()
{
	delete this->camera;

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].getMesh()->deleteBuffers();
	}
}
