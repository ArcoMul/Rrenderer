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
		void setRotation(Vector3 vector);
		void setNear(float n);
		void setFar(float n);
		void setAspect(float n);
		void setFOV(float angle);

		void translate(Vector3 vector);
		void rotate(Vector3 vector);

		void recalculateViewMatrix();
		void recalculateProjectMatrix();

		Vector3 getPosition();
		Vector3 getRotation();
		Matrix4* getViewMatrix();
		Matrix4* getProjectionMatrix();
	private:
		bool orthoGrahpic;
		float near;
		float far;
		float aspect;
		float FOV;

		Vector3 position;
		Vector3 rotation;
		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;
	};
}

