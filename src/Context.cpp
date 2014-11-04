#include "stdafx.h"
#include <GLFW/glfw3.h>
#include "Context.h"
#include "Triangle.h"

Context::Context()
{

}

void Context::render(GLFWwindow* window)
{
	// Get the time defined by glfw
	double time = glfwGetTime();

	float ratio;
	int width, height;

	// Get the size of the window / buffer
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
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].render(this);
	}
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Context::addMesh(Mesh mesh)
{
	meshes.push_back(mesh);
}

void Context::setColor()
{
	glColor3f(1.f, 0.f, 0.f);
}

void Context::drawVertex(float vertex[3])
{
	glVertex3f(vertex[0], vertex[1], vertex[2]);
}

Context::~Context()
{
}
