#pragma once

#include <GL/glew.h>
#include "Rrenderer.h"

class GLFWwindow;

namespace Rr
{
	class Mesh;
	class Object;

	class RRENDERER_API VideoDriver
	{
	public:
		VideoDriver();
		~VideoDriver();

		bool init();
		bool createWindow(int x, int y, char* title);
		GLFWwindow* getWindow();
		double getTime();
		bool windowShouldClose();

		GLuint createAndCompileShader(GLuint type, char* source);
		void debugShader(GLuint object);

		void prepareFrame();
		void finishFrame();
		void generateVertexArray(GLuint* vao);
		void bufferVertexes(GLuint* vbo, GLuint* vao, int n, float points[]);
		void bufferNormals(GLuint* nbo, GLuint* vao, int n, float normals[]);
		void renderObject(Object* object);

		void setUniform4f(char* name, float v1, float v2, float v3, float v4);
		void setUniform3f(char* name, float v1, float v2, float v3);
		void setUniform1f(char* name, float v1);
	private:
		GLFWwindow* window;
		GLuint shaderProgramme;
	};
}

