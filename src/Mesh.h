#pragma once

#include "Rrenderer.h"
#include <GL/glew.h>
#include <vector>

namespace Rr
{
	class RRENDERER_API Mesh
	{
	public:
		// Initializes a new mesh, sets up the vertex array in GL
		Mesh();

		// Deletes the generated GL buffers of this mesh
		~Mesh();

		// Sets the points / vertexes of this mesh, also buffers them to GL
		void setPoints(std::vector<float> points);

		// Sets the normals of this mesh, also buffers them to GL
		void setNormals(std::vector<float> normals);

		// Get the amount of points in this mesh
		int getPointCount();

		// Delete all the OpenGL buffers set by this mesh
		void deleteBuffers();

		// Vertex Array Object
		GLuint vao;

		// Vertex Buffer Object
		GLuint vbo;

		// Normal Buffer Object
		GLuint nbo;
		
	private:
		std::vector<float> points;
		std::vector<float> normals;
	};
}
