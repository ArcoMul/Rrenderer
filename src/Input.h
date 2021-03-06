#pragma once

#include "Rrenderer.h"
#include "Vector3.h"

namespace Rr
{
	class RRENDERER_API Input
	{
	public:
		Input();
		~Input();

		bool isPressed(int key);
		void setPressed(int key, bool pressed);

		bool keysDown[100];

		static const int KEY_W = 87;
		static const int KEY_A = 65;
		static const int KEY_S = 83;
		static const int KEY_D = 68;
		static const int KEY_SPACE = 32;
		static const int KEY_SHIFT = 340;

		void setMousePosition(double x, double y);
		Vector3 getMousePosition();
		Vector3 getMousePositionDelta();

		Vector3 mousePosition;
		Vector3 mousePositionDelta;
	};
}
