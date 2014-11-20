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
		~Parser();

		// Parses a .obj file to a corresponding Mesh
		Mesh parse(std::string file);
	};
}