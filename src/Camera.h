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
		void setNear(float n);
		void setFar(float n);
		void setAspect(float n);
		void setFOV(float angle);

		void recalculateProjectMatrix();

		Vector3 getPosition();
		Matrix4* getViewMatrix();
		Matrix4* getProjectionMatrix();
	private:
		bool orthoGrahpic;
		float near;
		float far;
		float aspect;
		float FOV;

		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;
	};
}

