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
	if (health > 0)
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
			right->Draw(0, position.x - 8, position.y);
		}
	}
}

void Spy::calcNewPos(Point _position)
{
	position.x += width;
	position.y += height;
	float theta = atan(-1 * (_position.y - position.y) / (_position.x - position.x));
	switch (mode)
	{
	case follow:

		if (_position.x > position.x) {
			yVel = sin(theta) * -1 * speed;
			xVel = cos(theta) * speed;
		}
		else {
			yVel = sin(theta) * speed;
			xVel = cos(theta) * -1 * speed;
		}
		break;
	case hover:
		if (yVel > 1)
		{
			hovermode = rise;
		}
		if (yVel < -1)
		{
			hovermode = fall;
		}
		switch (hovermode)
		{
		case fall:
			yVel += 0.05;
			break;
		case rise:
			yVel -= 0.05;
			break;
		}
		break;
	}
	position.x -= width;
	position.y -= height;
}

void Spy::load()
{
	left = new SpriteSheet(L"spy_left.png", 16, 8, 0, 1, gfx);
	right = new SpriteSheet(L"spy_right.png", 16, 8, 0, 1, gfx);
	up = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
	down = new SpriteSheet(L"spy_down.png", 8, 16, 0, 1, gfx);
	normal = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
	health = 10;
	speed = 1.5;
	hovermode = rise;
	mode = hover;
}
void Spy::subtractHealth(int _amount)
{
	health -= _amount;
}
int Spy::getHealth()
{
	return health;
}
void Spy::setMode(behaviorType _mode)
{
	mode = _mode;
}