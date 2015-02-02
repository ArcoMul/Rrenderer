#include <Renderer.h>
#include <VideoDriver.h>
#include <Parser.h>
#include <Context.h>
#include <Mesh.h>
#include <Color.h>
#include <Material.h>
#include <Object.h>
#include <Camera.h>
#include <Vector3.h>
#include <Matrix4.h>

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
	Rr::Renderer::instance()->video->createWindow(800, 600, "Shaders!");

	// Load the ball mesh
	Rr::Mesh ballMesh;
	Rr::Renderer::instance()->parser->parse("../assets/ball.obj", &ballMesh);

	// Create the ball material
	Rr::Material ballMaterial = Rr::Material();
	ballMaterial.setBaseColor(Rr::Color(0, 125, 255));
	ballMaterial.setAmbient(0.3);
	ballMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	// Create the ball object and link the mesh and material on it
	Rr::Object ball;
	ball.setMesh(ballMesh);
	ball.setMaterial(ballMaterial);

	// Add the ball to the context
	Rr::Renderer::instance()->context->addObject(ball);

	// Load the monkey mesh
	Rr::Mesh monkeyMesh;
	Rr::Renderer::instance()->parser->parse("../assets/monkey.obj", &monkeyMesh);

	// Create the monkey material
	Rr::Material monkeyMaterial = Rr::Material();
	monkeyMaterial.setBaseColor(Rr::Color(255, 125, 0));
	monkeyMaterial.setAmbient(0.2);
	monkeyMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	// Create the monkey object and link the mesh and material on it
	Rr::Object monkey;
	monkey.setMesh(monkeyMesh);
	monkey.setMaterial(monkeyMaterial);
	monkey.setPosition(Rr::Vector3(0.0, 0.0, 0.0));

	// Add the monkey to the context
	Rr::Renderer::instance()->context->addObject(monkey);

	Rr::Camera camera = Rr::Camera();
	camera.setPosition(Rr::Vector3(-0.5, -0.5, -3));
	Rr::Renderer::instance()->context->setCamera(camera);

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