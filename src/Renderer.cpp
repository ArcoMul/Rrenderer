#include "stdafx.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <thread>
#include <iostream>

#include "Context.h"
#include "Parser.h"

Rr::Renderer* Rr::Renderer::m_pInstance = NULL;

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

Rr::Renderer::Renderer()
{
	
}

void Rr::Renderer::init()
{
	// Set the error callback in case of glfw errors
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	context = new Context();
	parser = new Parser();
}

void Rr::Renderer::run()
{
	while (!glfwWindowShouldClose(window))
	{
		context->render(window);
	}

	this->stop();
}

void Rr::Renderer::stop()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

Rr::Renderer* Rr::Renderer::instance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new Renderer;

	return m_pInstance;
}

Rr::Renderer::~Renderer()
{
}
