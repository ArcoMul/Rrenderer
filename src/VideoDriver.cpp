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

	// Clear the bugger
	glClear(GL_COLOR_BUFFER_BIT);

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

	glBegin(GL_TRIANGLES);
}

void VideoDriver::finishFrame()
{
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void VideoDriver::renderMesh(Mesh* mesh)
{
	std::vector<Triangle>* triangles = mesh->getTriangles();
	for (int i = 0; i < triangles->size(); i++)
	{
		setColor();
		float* vertexes = triangles->at(i).getVertexes();
		drawVertex(vertexes + 0 * 3);
		drawVertex(vertexes + 1 * 3);
		drawVertex(vertexes + 2 * 3);
	}
}

void VideoDriver::setColor()
{
	glColor3f(1.f, 0.f, 0.f);
}

void VideoDriver::drawVertex(float* vertex)
{
	glVertex3f(*vertex, *(vertex + 1), *(vertex + 2));
}

VideoDriver::~VideoDriver()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
