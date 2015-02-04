#pragma once

#include "Rrenderer.h"
#include <vector>
#include "Object.h"
#include "Camera.h"

class VideoDriver;

namespace Rr
{
	class RRENDERER_API Context
	{
	public:
		Context();
		~Context();

		// Renders all the objects in this context
		void render();

		// Adds a new object to this context
		void addObject(Object object);

		void setCamera(Camera* camera);

	private:
		// Reference to the video driver, since it is used a lot
		VideoDriver* video;

		// The objects to be rendered in this context
		std::vector<Object> objects;

		Camera* camera;
	};
}

