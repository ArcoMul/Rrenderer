#include <cstdio>

#include <Renderer.h>
#include <VideoDriver.h>
#include <Parser.h>
#include <Context.h>
#include <Input.h>
#include <Mesh.h>
#include <Color.h>
#include <Material.h>
#include <Object.h>
#include <Camera.h>
#include <Vector3.h>
#include <Matrix4.h>

void start()
{

}

Rr::Camera* camera;

void update(float deltaTime)
{
	Rr::Vector3 pos = Rr::Vector3();
	Rr::Vector3 rot = Rr::Vector3();
	Rr::Vector3 delta = Rr::Renderer::instance()->input->getMousePositionDelta();

	if (delta.x != 0 || delta.y != 0) {
		rot.y -= delta.x / 20;
		rot.x -= delta.y / 20;
		camera->rotate(rot);
	}	

	if (Rr::Renderer::instance()->input->isPressed(Rr::Input::KEY_W)) {
		pos.z += 0.05;
	}

	if (Rr::Renderer::instance()->input->isPressed(Rr::Input::KEY_S)) {
		pos.z -= 0.05;
	}

	if (Rr::Renderer::instance()->input->isPressed(Rr::Input::KEY_A)) {
		pos.x += 0.05;
	}

	if (Rr::Renderer::instance()->input->isPressed(Rr::Input::KEY_D)) {
		pos.x -= 0.05;
	}

	if (Rr::Renderer::instance()->input->isPressed(Rr::Input::KEY_SPACE)) {
		pos.y -= 0.05;
	}

	camera->translate(pos);
}

int main(int argc, char* argv[])
{
	// Create the first instance / check if the instance is created successfully
	if (!Rr::Renderer::instance()) {
		printf("Renderer not started");
		return 0;
	}

	Rr::Renderer::instance()->bindUpdate(&update);
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
	Rr::Renderer::instance()->context->addObject(monkey);

	Rr::Object monkey2;
	monkey2.setMesh(monkeyMesh);
	monkey2.setMaterial(monkeyMaterial);
	monkey2.setPosition(Rr::Vector3(3.0, 0.0, 0.0));
	Rr::Renderer::instance()->context->addObject(monkey2);

	Rr::Object monkey3;
	monkey3.setMesh(monkeyMesh);
	monkey3.setMaterial(monkeyMaterial);
	monkey3.setPosition(Rr::Vector3(-3.0, 0.0, 0.0));
	Rr::Renderer::instance()->context->addObject(monkey3);

	camera = new Rr::Camera();
	camera->setPosition(Rr::Vector3(0.0, 0.0, 3));
	camera->setRotation(Rr::Vector3(0.0, 180.0, 0.0));
	Rr::Renderer::instance()->context->setCamera(camera);

	// Start running the engine
	Rr::Renderer::instance()->run();

	// Destroy the render engine and its components
	Rr::Renderer::instance()->destroy();

	return 0;
}