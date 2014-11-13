#include "VideoDriver.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Mesh.h"
#include "Triangle.h"

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

VideoDriver::VideoDriver()
{
	
}

bool VideoDriver::init()
{
	// Set the error callback in case of glfw errors
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		return false;
	}

	return true;
}

bool VideoDriver::createWindow(int x, int y, char* title)
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
}

void VideoDriver::setVertexShader(const char* shader)
{
	this->vertexShader = shader;
}

void VideoDriver::setFragmentShader(const char* shader)
{
	this->fragmentShader = shader;
}

void VideoDriver::compileShaders()
{
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShader, NULL);
	glCompileShader(fs);

	shaderProgramme = glCreateProgram();
	glAttachShader(shaderProgramme, fs);
	glAttachShader(shaderProgramme, vs);
	glLinkProgram(shaderProgramme);

	debugShader(shaderProgramme);
}

void VideoDriver::debugShader(GLuint object)
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

GLFWwindow* VideoDriver::getWindow()
{
	return window;
}

double VideoDriver::getTime()
{
	return glfwGetTime();
}

bool VideoDriver::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void VideoDriver::prepareFrame()
{
	// Get the size of the window / buffer
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	// Set the viewport for the coming calls
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramme);

	// Set the matrix mode PROJECTION
	glMatrixMode(GL_PROJECTION);

	// Replace the current matrix with the identity matrix
	glLoadIdentity();

	// Multiply the current matrix with an orthographic matrix
	// TODO: what does this line do?
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	// Switch to matrix mode, MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void VideoDriver::finishFrame()
{
	// put the stuff we've been drawing onto the display
	glfwSwapBuffers(window);

	// update other events like input handling 
	glfwPollEvents();
}

void VideoDriver::bufferVertexes(GLuint* vbo, GLuint* vao, int n, float points[])
{
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, n * sizeof(float), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void VideoDriver::renderMesh(Mesh* mesh)
{
	glBindVertexArray(mesh->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, mesh->getPointCount());
}

VideoDriver::~VideoDriver()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
