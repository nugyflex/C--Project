#include "Spy.h"
#include "stdio.h"
#include <math.h>

Spy::Spy() {}

Spy::Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi) :
	Rect(_position, _width, _height, _yVel, _xVel, false, spy, false, gfxi)
{

}

Spy::~Spy()
{
}

void Spy::draw()
{
	if (yVel < 0)
	{
		up->Draw(0, position.x, position.y);
	}
	if (yVel >= 0)
	{
		down->Draw(0, position.x, position.y);
	}
	if (xVel < 0)
	{
		left->Draw(0, position.x, position.y);
	}
	if (xVel > 0)
	{
		right->Draw(0, position.x-8, position.y);
	}
}

void Spy::calcNewPos(Point _position)
{
	if (position.x < _position.x) {
		setxVel(floor((_position.x - position.x) / 35));
	}
	if (position.x > _position.x) {
		setxVel(floor((position.x - _position.x) / -35));
	}
	if (position.y < _position.y) {
		setyVel(floor(((_position.y - 10) - position.y) / 35));
	}
	if (position.y > _position.y) {
		setyVel(floor((position.y - (_position.y - 10)) / -35));
	}
}

void Spy::load()
{
	left = new SpriteSheet(L"spy_left.png", 16, 8, 0, 1, gfx);
	right = new SpriteSheet(L"spy_right.png", 16, 8, 0, 1, gfx);
	up = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
	down = new SpriteSheet(L"spy_down.png", 8, 16, 0, 1, gfx);
	normal = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
}