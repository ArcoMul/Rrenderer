#include "Renderer.h"

#include "VideoDriver.h"
#include "Context.h"
#include "Parser.h"
#include "Input.h"

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
	input = new Input();

	return true;
}

void Rr::Renderer::run()
{
	while (!video->windowShouldClose())
	{
		callBindedUpdate();

		video->prepareFrame();
		context->render();
		video->finishFrame();
	}
}

void Rr::Renderer::bindUpdate(std::function<void(float)> f)
{
	bindedUpdate = f;
}

void Rr::Renderer::callBindedUpdate()
{
	bindedUpdate(0.0);
}

void Rr::Renderer::destroy()
{
	delete context;
	delete parser;
	delete video;
	delete input;
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
