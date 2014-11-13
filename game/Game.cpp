#include <Renderer.h>
#include <VideoDriver.h>
#include <Parser.h>
#include <Context.h>
#include <Mesh.h>

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

	Rr::Renderer::instance()->video->createWindow(640, 480, "My Title");
	Rr::Renderer::instance()->video->setVertexShader(
		"#version 400\n"
		"in vec3 vp;"
		"void main () {"
		"  gl_Position = vec4 (vp, 1.0);"
		"}"
	);
	Rr::Renderer::instance()->video->setFragmentShader(
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main () {"
		"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}"
	);
	Rr::Renderer::instance()->video->compileShaders();

	// Parse an .obj file to a new mesh
	Mesh mesh = Rr::Renderer::instance()->parser->parse("../assets/test.obj");

	// Add the mesh to the current context
	Rr::Renderer::instance()->context->addMesh(mesh);

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