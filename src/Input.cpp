#include "Input.h"

#include <algorithm>

Rr::Input::Input()
{
	std::fill_n(keysDown, 100, 0);
}

Rr::Input::~Input()
{
}

bool Rr::Input::isPressed (int key)
{
	return keysDown[key];
}

void Rr::Input::setPressed(int key, bool pressed)
{
	keysDown[key] = pressed;
}