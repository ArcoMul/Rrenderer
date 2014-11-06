#pragma once

#include "Rrenderer.h"

class VideoDriver;
class Parser;
class Context;

namespace Rr
{
	class RRENDERER_API Renderer
	{
	public:
		static Renderer* instance();

		Renderer();
		~Renderer();

		bool init();
		void run();
		void destroy();

		VideoDriver* video;
		Parser* parser;
		Context* context;
	private:
		static Renderer* m_pInstance;
	};
}
