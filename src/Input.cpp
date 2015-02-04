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

void Rr::Input::setMousePosition(double x, double y)
{
	double deltaX = this->mousePosition.x - x;
	double deltaY = this->mousePosition.y - y;
	this->mousePositionDelta.x = abs(deltaX) < 50 ? deltaX : 0;
	this->mousePositionDelta.y = abs(deltaY) < 50 ? deltaY : 0;
	this->mousePosition.x = x;
	this->mousePosition.y = y;
}

Rr::Vector3 Rr::Input::getMousePosition()
{
	return this->mousePosition;
}

Rr::Vector3 Rr::Input::getMousePositionDelta()
{
	return this->mousePositionDelta;
}