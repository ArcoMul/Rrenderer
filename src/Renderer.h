#pragma once

#include "Rrenderer.h"

struct GLFWwindow;
class Parser;
class Context;

namespace Rr
{
	class RRENDERER_API Renderer
	{
	public:
		static Renderer* instance();

		Renderer();
		void init();
		void run();
		void stop();
	    ~Renderer();

		GLFWwindow* window;
		Parser* parser;
		Context* context;
	private:
		static Renderer* m_pInstance;
	};
}
