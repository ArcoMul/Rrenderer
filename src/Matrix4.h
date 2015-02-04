#pragma once

#include "Rrenderer.h"
#include "Vector3.h"

namespace Rr
{
	class RRENDERER_API Matrix4
	{
	public:
		Matrix4();
		~Matrix4();

		float operator [](int i) const { return points[i]; }
		float & operator [](int i) { return points[i]; }
		Matrix4 operator* (Matrix4 other);

		void translate(Vector3 vector);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);

		void toIdentity();
		Matrix4 inverse();
		float* toArray() { return points; }
		void print();
	private:
		float points[16];
	};
}

