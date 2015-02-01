#pragma once

#include <GL/glew.h>
#include "Rrenderer.h"
#include "Camera.h"

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

		// Initializes glfw
		bool init();

		// Creates a glfw window
		bool createWindow(int x, int y, char* title);

		// Returns the current glfw window, only one supported at the moment
		GLFWwindow* getWindow();

		// Returns the glfw time
		double getTime();

		// Returns true if the window should close, based on if the escape key is pressed
		bool windowShouldClose();

		// Compiles a source string as a certain shader defined by <GLuint type>
		GLuint createAndCompileShader(GLuint type, char* source);

		// Print any error message of just compiled/linked/used shaders
		void debugShader(GLuint object);

		// Collection of opengl calls to prepare the rendering of the context
		void prepareFrame();

		// Draws all the triangles of an object and applies the correct shaders
		//  based on the material
		void renderObject(Object* object);

		// Collection of opengl calls to display the just rendered frame
		void finishFrame();

		void setActiveCamera(Camera* camera);

		// Generate a new vertex array, puts the id in the given pointer
		void generateVertexArray(GLuint* vao);

		// Buffers an array with vertex points
		// vbo: will get the reference to the new buffer
		// vao: vertex array this buffer should be put in
		// points[]: the vertexes to buffer
		void bufferVertexes(GLuint* vbo, GLuint* vao, int n, float points[]);

		// Buffers an array with normals
		// nbo: will get the reference to the new buffer
		// vao: vertex array this buffer should be put in
		// normals[]: the normals to buffer
		void bufferNormals(GLuint* nbo, GLuint* vao, int n, float normals[]);

		// Deletes the buffer from the GL memeory
		void deleteBuffer(GLuint* buffer);

		// Wrapper functions to set Uniforms in OpenGL
		void setUniform4fv(char* name, float* matrix);
		void setUniform4f(char* name, float v1, float v2, float v3, float v4);
		void setUniform3f(char* name, float v1, float v2, float v3);
		void setUniform1f(char* name, float v1);

	private:
		// Our current and only glfw window
		GLFWwindow* window;

		// The shader programme we use to compile and link our shaders to
		GLuint shaderProgramme;

		Camera* activeCamera;
	};
}

