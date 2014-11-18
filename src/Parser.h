#pragma once

#include "Rrenderer.h"
#include <string>

namespace Rr
{
	class Mesh;

	class RRENDERER_API Parser
	{
	public:
		Parser();
		Mesh parse(std::string file);
		~Parser();
	};
}