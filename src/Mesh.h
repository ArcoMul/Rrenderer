#pragma once

#include "Rrenderer.h"
#include <GL/glew.h>
#include <vector>

namespace Rr
{
	class RRENDERER_API Mesh
	{
	public:
		Mesh();
		void setPoints(std::vector<float> points);
		void setNormals(std::vector<float> normals);
		int getPointCount();
		GLuint vbo;
		GLuint nbo;
		GLuint vao;
		~Mesh();
	private:

		std::vector<float> points;
		std::vector<float> normals;
	};
}
