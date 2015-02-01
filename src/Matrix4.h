#pragma once

#include "Rrenderer.h"

namespace Rr
{
	class RRENDERER_API Matrix4
	{
	public:
		Matrix4();
		~Matrix4();

		float operator [](int i) const { return points[i]; }
		float & operator [](int i) { return points[i]; }

		float* toArray() { return points; }
		void print();
	private:
		float points[16];
	};
}

