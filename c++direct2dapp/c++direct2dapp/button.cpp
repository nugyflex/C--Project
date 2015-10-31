#include "button.h"
Button::Button()
{
}
Button::Button(int _x, int _y, Graphics * _gfx)
{
	gfx = _gfx;
	position.x = _x;
	position.y = _y;
}
Button::~Button() {}

void Button::action() {}

void Button::draw() {}

Point Button::getPosition()
{
	return position;
}