#pragma once

#include "Rrenderer.h"
#include <GL/glew.h>
#include "Color.h"

namespace Rr
{
	class RRENDERER_API Material
	{
	public:
		Material();
		~Material();

		void setDiffuse(Color color);
		void setSpecular(Color color);
		void setShininess(float value);
		void setVertexShader(char* source);
		void setFragmentShader(char* source);

		GLuint* getVertexShader();
		GLuint* getFragmentShader();
		Color getDiffuse();
	private:
		Color diffuse;
		Color specular;
		float shininess;
		GLuint vertexShader;
		GLuint fragmentShader;
	};
}

