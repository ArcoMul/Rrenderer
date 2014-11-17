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

	// TODO: move shader + unifroms to material object
	Rr::Renderer::instance()->video->createWindow(640, 480, "My Title");
	Rr::Renderer::instance()->video->setVertexShader(
		"#version 330 core\n"
		// "uniform mat4 MVPMatrix;"
		// "uniform mat3 NormalMatrix;" // to transform normals, pre-perspective
		// "in vec4 VertexColor;"
		"layout(location = 0) in vec4 VertexPosition;"
		"layout(location = 1) in vec3 VertexNormal;"
		"out vec4 Color;"
		"out vec3 Normal;"
		"void main()"
		"{"
			"Color = vec4(.5, .5, .5, 1.);"
			// transform the normal, without perspective, and normalize it
			// "Normal = normalize(NormalMatrix * VertexNormal);"
			// "gl_Position = MVPMatrix * VertexPosition;"
			"Normal = VertexNormal;"
			"gl_Position = VertexPosition;"
		"}"
	);
	Rr::Renderer::instance()->video->setFragmentShader(
		"#version 330 core\n"
		"uniform vec3 Ambient;"
		"uniform vec3 LightColor;"
		"uniform vec3 LightDirection;"
		"uniform vec3 HalfVector;"
		"uniform float Shininess;"
		"uniform float Strength;"
		"in vec4 Color;"
		"in vec3 Normal;"
		"out vec4 FragColor;"
		"void main()"
		"{"
			// compute cosine of the directions, using dot products,
			// to see how much light would be reflected
			"float diffuse = max(0.0, dot(Normal, LightDirection));"
			"float specular = max(0.0, dot(Normal, HalfVector));"
			// surfaces facing away from the light (negative dot products)
			// won’t be lit by the directional light
			"if (diffuse == 0.0) {"
				"specular = 0.0;"
			"} else {"
				"specular = pow(specular, Shininess);" // sharpen the highlight
			"}"
			"vec3 scatteredLight = Ambient + LightColor * diffuse;"
			"vec3 reflectedLight = LightColor * specular * Strength;"
			// don’t modulate the underlying color with reflected light,
			// only with scattered light
			"vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));"
			"FragColor = vec4(rgb, Color.a);"
		"}"
	);
	Rr::Renderer::instance()->video->compileShaders();
	Rr::Renderer::instance()->video->setUniform4f("Ambient", .5, .5, .5, 1.);
	Rr::Renderer::instance()->video->setUniform3f("LightColor", .5, .5, .5);
	Rr::Renderer::instance()->video->setUniform3f("LightDirection", 0., 0., -1.);
	Rr::Renderer::instance()->video->setUniform3f("HalfVector", 0., 0., 0.);
	Rr::Renderer::instance()->video->setUniform1f("Shininess", 0.5);
	Rr::Renderer::instance()->video->setUniform1f("Strength", 0.5);

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