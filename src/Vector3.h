#pragma once

#include "Rrenderer.h"

namespace Rr
{
	class RRENDERER_API Vector3
	{
	public:
		Vector3(float x, float y, float z);
		~Vector3();

		float x() { return points[0]; }
		float y() { return points[1]; }
		float z() { return points[2]; }
	private:
		float points[3];
	};
}

