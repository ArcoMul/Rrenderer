#pragma once

#include "Rrenderer.h"

namespace Rr
{
	class RRENDERER_API Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();

		float x;
		float y;
		float z;
	};
}

