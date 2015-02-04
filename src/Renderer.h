#pragma once

#include "Rrenderer.h"
#include <vector>
#include <functional>

namespace Rr
{
	class VideoDriver;
	class Parser;
	class Context;
	class Input;

	class RRENDERER_API Renderer
	{
	public:
		static Renderer* instance();

		Renderer();
		~Renderer();

		bool init();
		void run();
		void destroy();

		void bindUpdate(std::function<void(float)> f);
		void callBindedUpdate();

		VideoDriver* video;
		Parser* parser;
		Context* context;
		Input* input;
	private:
		static Renderer* m_pInstance;

		std::function<void(float)> bindedUpdate;
	};
}
