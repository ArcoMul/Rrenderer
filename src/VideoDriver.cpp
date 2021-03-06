#include "VideoDriver.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Renderer.h"
#include "Input.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Object.h"
#include "Camera.h"
#include "Mesh.h"

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS) {
		Rr::Renderer::instance()->input->setPressed(key, true);
	}

	if (action == GLFW_RELEASE) {
		Rr::Renderer::instance()->input->setPressed(key, false);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Rr::Renderer::instance()->video->setViewportSize(window, width, height);
}

Rr::VideoDriver::VideoDriver()
{
	
}

bool Rr::VideoDriver::init()
{
	// Set the error callback in case of glfw errors
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		return false;
	}

	return true;
}

bool Rr::VideoDriver::createWindow(int x, int y, char* title)
{
	window = glfwCreateWindow(x, y, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// Get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// Tell OpenGL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	shaderProgramme = glCreateProgram();
}

void Rr::VideoDriver::setViewportSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	activeCamera->setAspect(static_cast<float>(width) / static_cast<float>(height));
}

GLuint Rr::VideoDriver::createAndCompileShader(GLuint type, char* source)
{
	// Create a new shader object
	GLuint shader = glCreateShader(type);
	// Set the source code of the shader
	glShaderSource(shader, 1, &source, NULL);
	// Compile the source code to a shader object
	glCompileShader(shader);

	return shader;
}

void Rr::VideoDriver::debugShader(GLuint object)
{
	GLint log_length = 0;
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*)malloc(log_length);

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);

	fprintf(stderr, "%s", log);
	free(log);
}

GLFWwindow* Rr::VideoDriver::getWindow()
{
	return window;
}

double Rr::VideoDriver::getTime()
{
	return glfwGetTime();
}

bool Rr::VideoDriver::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Rr::VideoDriver::prepareFrame()
{
	// Get the size of the window / buffer
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	// Set the viewport for the coming calls
	glViewport(0, 0, width, height);

	// Clear the current view
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The following calls affect the protection matrix
	glMatrixMode(GL_PROJECTION);

	// Set the identity matrix as the current (projection) matrix
	glLoadIdentity();

	// Multiply the current matrix with an orthographic matrix
	// TODO: I don't really understand what this does
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	// The coming calls affect the modelview matrix
	glMatrixMode(GL_MODELVIEW);

	// Set the identity matrix as the current (modelview) matrix
	glLoadIdentity();
}

void Rr::VideoDriver::renderObject(Object* object)
{
	// Attach the shaders we want to use
	glAttachShader(shaderProgramme, *object->getMaterial()->getVertexShader());
	glAttachShader(shaderProgramme, *object->getMaterial()->getFragmentShader());

	// Tell which vertex array to render
	glBindVertexArray(object->getMesh()->vao);

	// Link the uniforms to the programme
	glLinkProgram(shaderProgramme);

	// Tell which programme to use
	glUseProgram(shaderProgramme);

	setUniform4f("ObjectColor", object->getMaterial()->getBaseColor().r() / 255.f, object->getMaterial()->getBaseColor().g() / 255.f, object->getMaterial()->getBaseColor().b() / 255.f, 1);
	setUniform3f("Ambient", object->getMaterial()->getAmbient(), object->getMaterial()->getAmbient(), object->getMaterial()->getAmbient());
	setUniform3f("LightColor", object->getMaterial()->getSpecularColor().r() / 255.f, object->getMaterial()->getSpecularColor().g() / 255.f, object->getMaterial()->getSpecularColor().b() / 255.f);
	setUniform1f("Shininess", object->getMaterial()->getSpecularStrength());
	setUniform1f("Strength", object->getMaterial()->getSpecularStrength());

	setUniform4fv("ProjectionMatrix", activeCamera->getProjectionMatrix()->toArray());
	setUniform4fv("ViewMatrix", activeCamera->getViewMatrix()->toArray());
	setUniform4fv("ModelMatrix", object->getModelMatrix()->toArray());

	setUniform3f("HalfVector", 0., 0., 0.);
	setUniform3f("LightDirection", 1., 1., -1.);

	// Check if there are any errors
	debugShader(shaderProgramme);

	// Draw!
	glDrawArrays(GL_TRIANGLES, 0, object->getMesh()->getPointCount());

	// Detach the shaders from the programm
	glDetachShader(shaderProgramme, *object->getMaterial()->getVertexShader());
	glDetachShader(shaderProgramme, *object->getMaterial()->getFragmentShader());
}

void Rr::VideoDriver::finishFrame()
{
	// Put the stuff we've been drawing onto the display
	glfwSwapBuffers(window);

	// Update other events like input handling 
	glfwPollEvents();

	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	Rr::Renderer::instance()->input->setMousePosition(x, y);

	if (x < 50) { glfwSetCursorPos(window, 750, y); }
	if (x > 750) { glfwSetCursorPos(window, 50, y); }
	if (y < 50) { glfwSetCursorPos(window, x, 550); }
	if (y > 550) { glfwSetCursorPos(window, x, 50); }
}

void Rr::VideoDriver::setActiveCamera(Rr::Camera* camera)
{
	this->activeCamera = camera;
}	


void Rr::VideoDriver::generateVertexArray(GLuint* vao)
{
	glGenVertexArrays(1, vao);
}

void Rr::VideoDriver::bufferVertexes(GLuint* vbo, GLuint* vao, int n, float points[])
{
	// Buffer the points
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, n * sizeof(GLfloat), points, GL_STATIC_DRAW);

	glBindVertexArray(*vao);

	// Bind the buffer to the vertex array of the object
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Rr::VideoDriver::bufferNormals(GLuint* nbo, GLuint* vao, int n, float normals[])
{
	// Buffer the normals
	glGenBuffers(1, nbo);
	glBindBuffer(GL_ARRAY_BUFFER, *nbo);
	glBufferData(GL_ARRAY_BUFFER, n * sizeof(GLfloat), normals, GL_STATIC_DRAW);

	glBindVertexArray(*vao);

	// Bind the buffer to the vertex array of the object
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, *nbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Rr::VideoDriver::deleteBuffer(GLuint* buffer)
{
	glDeleteBuffers(1, buffer);
}

void Rr::VideoDriver::setUniform4fv(char* name, float* matrix)
{
	GLuint id = glGetUniformLocation(shaderProgramme, name);
	glUniformMatrix4fv(id, 1, GL_TRUE, matrix);
}

void Rr::VideoDriver::setUniform4f(char* name, float v1, float v2, float v3, float v4)
{
	GLuint id = glGetUniformLocation(shaderProgramme, name);
	glUniform4f(id, v1, v2, v3, v4);
}

void Rr::VideoDriver::setUniform3f(char* name, float v1, float v2, float v3)
{
	GLuint id = glGetUniformLocation(shaderProgramme, name);
	glUniform3f(id, v1, v2, v3);
}

void Rr::VideoDriver::setUniform1f(char* name, float v1)
{
	GLuint id = glGetUniformLocation(shaderProgramme, name);
	glUniform1f(id, v1);
}

Rr::VideoDriver::~VideoDriver()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
