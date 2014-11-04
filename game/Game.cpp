// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Renderer.h>
#include <Parser.h>
#include <Context.h>
#include <Mesh.h>

int _tmain(int argc, _TCHAR* argv[])
{
	if (!Rr::Renderer::instance()) {
		printf("Renderer not started");
		return 0;
	}

	//renderer->bindUpdate(&update);
	//renderer->bindStart(&start);

	Rr::Renderer::instance()->init();
	Mesh mesh = Rr::Renderer::instance()->parser->parse("../assets/test.obj");
	Rr::Renderer::instance()->context->addMesh(mesh);
	Rr::Renderer::instance()->run();

	return 0;
}

void start()
{

}

void update()
{

}