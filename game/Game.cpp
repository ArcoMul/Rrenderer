// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Renderer.h>

int _tmain(int argc, _TCHAR* argv[])
{
	Rr::Renderer* renderer = new Rr::Renderer();
	if (!renderer) {
		printf("Renderer not started");
		return 0;
	}

	//renderer->bindUpdate(&update);
	//renderer->bindStart(&start);

	//renderer->start();

	//renderer->run();

	return 0;
}

void start()
{

}

void update()
{

}