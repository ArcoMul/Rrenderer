#include <Renderer.h>
#include <VideoDriver.h>
#include <Parser.h>
#include <Context.h>
#include <Mesh.h>
#include <Color.h>
#include <Material.h>
#include <Object.h>

int main(int argc, char* argv[])
{
	// Create the first instance / check if the instance is created successfully
	if (!Rr::Renderer::instance()) {
		printf("Renderer not started");
		return 0;
	}

	//renderer->bindUpdate(&update);
	//renderer->bindStart(&start);

	// Initialize the render engine and its components
	if (!Rr::Renderer::instance()->init()) {

	}

	// Create a window
	Rr::Renderer::instance()->video->createWindow(640, 480, "Shaders!");

	// Load the ball mesh
	Rr::Mesh ballMesh = Rr::Renderer::instance()->parser->parse("../assets/ball.obj");

	// Create the ball material
	Rr::Material ballMaterial = Rr::Material();
	ballMaterial.setDiffuse(Rr::Color(0, 125, 255, 255));
	ballMaterial.setSpecular(Rr::Color(.8, .8, .8, 1.));
	ballMaterial.setShininess(0.5);

	// Create the ball object and link the mesh and material on it
	Rr::Object ball;
	ball.setMesh(ballMesh);
	ball.setMaterial(ballMaterial);

	// Add the ball to the context
	Rr::Renderer::instance()->context->addObject(ball);

	// Load the monkey mesh
	Rr::Mesh monkeyMesh = Rr::Renderer::instance()->parser->parse("../assets/monkey.obj");

	// Create the monkey material
	Rr::Material monkeyMaterial = Rr::Material();
	monkeyMaterial.setDiffuse(Rr::Color(255, 125, 0, 255));
	monkeyMaterial.setSpecular(Rr::Color(.8, .8, .8, 1.));
	monkeyMaterial.setShininess(0.5);

	// Create the monkey object and link the mesh and material on it
	Rr::Object monkey;
	monkey.setMesh(monkeyMesh);
	monkey.setMaterial(monkeyMaterial);

	// Add the monkey to the context
	Rr::Renderer::instance()->context->addObject(monkey);

	// Start running the engine
	Rr::Renderer::instance()->run();

	// Destroy the render engine and its components
	Rr::Renderer::instance()->destroy();

	return 0;
}

void start()
{

}

void update()
{

}