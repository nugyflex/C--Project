#include "grenade.h"


Grenade::Grenade() {}

Grenade::Grenade(Point _position, float _xVel, float _yVel, int _timer, Graphics * gfxi) :
	Rect(_position, 9, 9, _xVel, _yVel, false, grenade, true, gfxi)
{
	timer = _timer;
	lastposition = position;
	load();
}

Grenade::~Grenade()
{
	delete image;
}

void Grenade::draw()
{
	if (lastposition.x < position.x)
	{
		lastposition.x -= (position.x - lastposition.x)*2;
	}
	else
	{
		lastposition.x += (lastposition.x - position.x)*2;
	}
	if (lastposition.y < position.y)
	{
		lastposition.y -= (position.y - lastposition.y)*2;
	}
	else
	{
		lastposition.y += (lastposition.y - position.y)*2;
	}
	//gfx->FillRect(position, width, height, 1, 0.7, 0.5, 1);
	image->Draw(0, position.x, position.y);
	gfx->DrawLine(position, lastposition, 0.9, 0.7, 0.6, 1);
	lastposition = position;
	timer--;
}

void Grenade::load()
{
	image = new SpriteSheet(L"bomb1.png", 9, 9, 0, 1, gfx);
}
int Grenade::getTimer()
{
	return timer;
}
void Grenade::calcNewPos()
{
	if (yVel > height)
	{
		yVel = height;
	}
	if (xVel > width)
	{
		xVel = width;
	}
	setX(getX() + getxVel());
	setY(getY() + getyVel());
}