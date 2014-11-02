#include "stdafx.h"
#include <GLFW/glfw3.h>
#include "Context.h"

#include "Vertex.h"
#include "Triangle.h"

Context::Context()
{
	triangle_count = 0;
	this->addTriangle(new Triangle(
		new Vertex(-0.6f, -0.4f, 0.f),
		new Vertex(0.6f, -0.4f, 0.f),
		new Vertex(0.f, 0.6f, 0.f)));

	this->addTriangle(new Triangle(
		new Vertex(-0.6f, -0.4f, 0.f),
		new Vertex(0.6f, -0.4f, 0.f),
		new Vertex(0.f, 0.6f, 0.f)));
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

	// glRotatef((float)time * 50.f, 0.f, 0.f, 1.f);

	// Draw a triangle

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < triangle_count; i++)
	{
		printf("Render triangle %d", i);
		triangles[i]->render(this);
	}
	//glColor3f(1.f, 0.f, 0.f);
	//glVertex3f(-0.8f, -0.4f, 0.f);
	//glColor3f(0.f, 1.f, 0.f);
	//glVertex3f(0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 0.f, 1.f);
	//glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Context::addTriangle(Triangle* triangle)
{
	triangles[triangle_count] = triangle;
	triangle_count++;
}

void Context::setColor()
{
	glColor3f(1.f, 0.f, 0.f);
}

void Context::drawVertex(Vertex* vertex)
{
	glVertex3f(vertex->getX(), vertex->getY(), vertex->getZ());
}

Context::~Context()
{
}
