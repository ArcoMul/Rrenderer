#pragma once

#include <GL/glew.h>
#include "Rrenderer.h"

class GLFWwindow;
class Mesh;

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

	void setVertexShader(const char* shader);
	void setFragmentShader(const char* shader);
	void compileShaders();
	void debugShader(GLuint object);

	void prepareFrame();
	void finishFrame();
	void bufferVertexes(GLuint* vbo, GLuint* vao, int n, float points[]);
	void bufferNormals(GLuint* nbo, GLuint* vao, int n, float normals[]);
	void renderMesh(Mesh* mesh);

	void setUniform4f(char* name, float v1, float v2, float v3, float v4);
	void setUniform3f(char* name, float v1, float v2, float v3);
	void setUniform1f(char* name, float v1);
private:
	GLFWwindow* window;
	GLuint shaderProgramme;
	const char* vertexShader;
	const char* fragmentShader;
	GLuint vao;
};

