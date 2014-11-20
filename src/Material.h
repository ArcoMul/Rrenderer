#pragma once

#include "Rrenderer.h"
#include <GL/glew.h>
#include "Color.h"

namespace Rr
{
	class RRENDERER_API Material
	{
	public:

		// Initializes the material, sets the hardcoded shaders
		Material();

		~Material();

		void setBaseColor(Color color);
		void setSpecular(float strength, Color color);
		void setAmbient(float strength);
		void setVertexShader(char* source);
		void setFragmentShader(char* source);

		Color getBaseColor();
		float getSpecularStrength();
		Color getSpecularColor();
		float getAmbient();
		GLuint* getVertexShader();
		GLuint* getFragmentShader();

	private:
		// Set the color this object will be by default
		Color baseColor;

		// The color of the reflected light of this material
		Color specularColor;

		// The amount of reflected light
		float specularStrength;

		// Set the amount of ambient light, more ambient is less dark shadows
		float ambientStrength;

		// The shaders of this material
		GLuint vertexShader;
		GLuint fragmentShader;
	};
}

