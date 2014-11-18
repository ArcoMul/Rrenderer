#pragma once

#include "Rrenderer.h"
#include <vector>
#include "Object.h"

class VideoDriver;

namespace Rr
{
	class RRENDERER_API Context
	{
	public:
		Context();
		void render();
		void addObject(Object object);
		~Context();
	private:
		VideoDriver* video;
		std::vector<Object> objects;
	};
}

