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
	Rr::Vector3 rot = camera->getRotation();
	Rr::Vector3 delta = Rr::Renderer::instance()->input->getMousePositionDelta();

	if (delta.x != 0 || delta.y != 0) {
		rot.y -= delta.x / 20;
		rot.x -= delta.y / 20;
		camera->setRotation(rot);
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

	/* Floor */
	Rr::Mesh floorMesh;
	Rr::Renderer::instance()->parser->parse("../assets/floor.obj", &floorMesh);

	Rr::Material floorMaterial = Rr::Material();
	floorMaterial.setBaseColor(Rr::Color(0, 255, 125));
	floorMaterial.setAmbient(0.2);
	floorMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	Rr::Object floor;
	floor.setMesh(floorMesh);
	floor.setMaterial(floorMaterial);

	Rr::Renderer::instance()->context->addObject(floor);

	/* House Walls */
	Rr::Mesh houseMesh;
	Rr::Renderer::instance()->parser->parse("../assets/house-walls.obj", &houseMesh);

	Rr::Material houseMaterial = Rr::Material();
	houseMaterial.setBaseColor(Rr::Color(241, 230, 155));
	houseMaterial.setAmbient(0.3);
	houseMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	Rr::Object house;
	house.setMesh(houseMesh);
	house.setMaterial(houseMaterial);

	Rr::Renderer::instance()->context->addObject(house);

	/* House Roof */
	Rr::Mesh roofMesh;
	Rr::Renderer::instance()->parser->parse("../assets/house-roof.obj", &roofMesh);

	Rr::Material roofMaterial = Rr::Material();
	roofMaterial.setBaseColor(Rr::Color(204, 77, 77));
	roofMaterial.setAmbient(0.3);
	roofMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	Rr::Object roof;
	roof.setMesh(roofMesh);
	roof.setMaterial(roofMaterial);

	Rr::Renderer::instance()->context->addObject(roof);

	/* Path */
	Rr::Mesh pathMesh;
	Rr::Renderer::instance()->parser->parse("../assets/path.obj", &pathMesh);

	Rr::Material pathMaterial = Rr::Material();
	pathMaterial.setBaseColor(Rr::Color(165, 165, 165));
	pathMaterial.setAmbient(0.2);
	pathMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	Rr::Object path;
	path.setMesh(pathMesh);
	path.setMaterial(pathMaterial);

	Rr::Renderer::instance()->context->addObject(path);

	/* Pool */
	Rr::Mesh poolMesh;
	Rr::Renderer::instance()->parser->parse("../assets/pool.obj", &poolMesh);

	Rr::Material poolMaterial = Rr::Material();
	poolMaterial.setBaseColor(Rr::Color(27, 188, 255));
	poolMaterial.setAmbient(0.2);
	poolMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	Rr::Object pool;
	path.setMesh(poolMesh);
	path.setMaterial(poolMaterial);

	Rr::Renderer::instance()->context->addObject(pool);


	/* Tree leaves */
	Rr::Mesh leavesMesh;
	Rr::Renderer::instance()->parser->parse("../assets/tree-leaves.obj", &leavesMesh);

	Rr::Material leavesMaterial = Rr::Material();
	leavesMaterial.setBaseColor(Rr::Color(49, 131, 27));
	leavesMaterial.setAmbient(0.2);
	leavesMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	Rr::Object leaves;
	leaves.setMesh(leavesMesh);
	leaves.setMaterial(leavesMaterial);
	leaves.setPosition(Rr::Vector3(0.0, 0.0, 3.0));
	Rr::Renderer::instance()->context->addObject(leaves);

	/* Tree trunk */
	Rr::Mesh trunkMesh;
	Rr::Renderer::instance()->parser->parse("../assets/tree-trunk.obj", &trunkMesh);

	Rr::Material trunkMaterial = Rr::Material();
	trunkMaterial.setBaseColor(Rr::Color(121, 69, 22));
	trunkMaterial.setAmbient(0.2);
	trunkMaterial.setSpecular(1, Rr::Color(200, 200, 200));

	Rr::Object trunk;
	trunk.setMesh(trunkMesh);
	trunk.setMaterial(trunkMaterial);
	trunk.setPosition(Rr::Vector3(0.0, 0.0, 3.0));
	Rr::Renderer::instance()->context->addObject(trunk);

	camera = new Rr::Camera();
	camera->setPosition(Rr::Vector3(0.0, -5.0, 12));
	camera->setRotation(Rr::Vector3(20.0, 180.0, 0.0));
	Rr::Renderer::instance()->context->setCamera(camera);

	// Start running the engine
	Rr::Renderer::instance()->run();

	// Destroy the render engine and its components
	Rr::Renderer::instance()->destroy();

	return 0;
}