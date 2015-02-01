#pragma once

#include "Rrenderer.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Rr
{
	class RRENDERER_API Camera
	{
	public:
		Camera();
		~Camera();

		void setPosition(Vector3 vector);
		Matrix4* getViewMatrix();
	private:
		bool orthoGrahpic;
		Matrix4 viewMatrix;
	};
}

