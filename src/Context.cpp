#include "stdafx.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Context.h"

#include "Vertex.h"
#include "Triangle.h"

Context::Context()
{
	triangle_count = 0;

	std::vector<Vertex*> vertexes;
	std::vector<int> faces;
	std::string line;
	std::ifstream myfile("../assets/test.obj");
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			if (line[0] == 'v')
			{
				std::string v, x, y, z;
				std::istringstream iss(line);
				iss >> v >> x >> z >> y;
				vertexes.push_back(new Vertex(::atof(x.c_str()), ::atof(y.c_str()), ::atof(z.c_str())));
			}
			if (line[0] == 'f')
			{
				std::string v, f1, f2, f3;
				std::istringstream iss(line);
				iss >> v >> f1 >> f2 >> f3;
				faces.push_back(std::stoi(f1));
				faces.push_back(std::stoi(f2));
				faces.push_back(std::stoi(f3));
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	for (int i = 0; i < faces.size(); i += 3)
	{
		this->addTriangle(new Triangle(
			vertexes[faces[i]-1],
			vertexes[faces[i+1]-1],
			vertexes[faces[i+2]-1]));
	}

	/*
	this->addTriangle(new Triangle(
		new Vertex(0.7f, 0.0f, -0.5f),
		new Vertex(0.13f, 0.0f, 0.0f),
		new Vertex(0.68f, 0.0f, 0.55f)));

	this->addTriangle(new Triangle(
		new Vertex(-0.1f, -0.2f, 0.f),
		new Vertex(-0.3f, -0.2f, 0.f),
		new Vertex(-0.2f, 0.3f, 0.f)));
		*/
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
