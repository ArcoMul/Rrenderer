#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <thread>
#include <iostream>

#include "VideoDriver.h"
#include "Context.h"
#include "Parser.h"

Rr::Renderer* Rr::Renderer::m_pInstance = NULL;

Rr::Renderer::Renderer()
{
	
}

bool Rr::Renderer::init()
{
	video = new VideoDriver();
	if (!video->init()) return false;

	context = new Context();
	parser = new Parser();

	return 1;
}

void Rr::Renderer::run()
{
	while (!video->windowShouldClose())
	{
		video->prepareFrame();
		context->render();
		video->finishFrame();
	}
}

void Rr::Renderer::destroy()
{
	delete context;
	delete parser;
	delete video;
	this->~Renderer();
}

Rr::Renderer* Rr::Renderer::instance()
{
	if (!m_pInstance)
		m_pInstance = new Renderer;

	return m_pInstance;
}

Rr::Renderer::~Renderer()
{
}
