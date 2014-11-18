#include "Material.h"
#include "Renderer.h"
#include "VideoDriver.h"

Rr::Material::Material()
{
	setVertexShader(
		"#version 330 core\n"
		// "uniform mat4 MVPMatrix;"
		// "uniform mat3 NormalMatrix;" // to transform normals, pre-perspective
		// "in vec4 VertexColor;"
		"layout(location = 0) in vec4 VertexPosition;"
		"layout(location = 1) in vec3 VertexNormal;"
		"uniform vec4 ObjectColor;"
		"out vec4 Color;"
		"out vec3 Normal;"
		"void main()"
		"{"
			"Color = ObjectColor;"
			// transform the normal, without perspective, and normalize it
			// "Normal = normalize(NormalMatrix * VertexNormal);"
			// "gl_Position = MVPMatrix * VertexPosition;"
			"Normal = VertexNormal;"
			"gl_Position = VertexPosition;"
		"}"
	);

	setFragmentShader(
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
}


Rr::Material::~Material()
{
}

void Rr::Material::setDiffuse(Color color)
{
	diffuse = color;
}

void Rr::Material::setSpecular(Color color)
{
	specular = color;
}

void Rr::Material::setShininess(float value)
{
	shininess = value;
}

void Rr::Material::setVertexShader(char* source)
{
	vertexShader = Rr::Renderer::instance()->video->createAndCompileShader(GL_VERTEX_SHADER, source);
}

void Rr::Material::setFragmentShader(char* source)
{
	fragmentShader = Rr::Renderer::instance()->video->createAndCompileShader(GL_FRAGMENT_SHADER, source);
}

GLuint* Rr::Material::getVertexShader()
{
	return &vertexShader;
}

GLuint* Rr::Material::getFragmentShader()
{
	return &fragmentShader;
}


Rr::Color Rr::Material::getDiffuse()
{
	return diffuse;
}