#include "gun.h"
Point mousePos;


Gun::Gun(float _x, float _y, Graphics * _gfx)
{
	position.x = _x;
	position.y = _y;
	gfx = _gfx;
	yVel = 0;
	xVel = 0;
}

Gun::~Gun()
{
}

void Gun::calcNewPos()
{
	if (hasParent)
	{
		
	}
	else
	{
		position.x += xVel;
		position.y += yVel;
	}
}
void Gun::drawOnParent(Point _position, int _offSetX, int  _offSetY)
{
	gfx->rotate(_position, (atan((mousePos.y - (position.y+10)) / (mousePos.x - position.x))));
	image->Draw(0, 0, 0);
	gfx->rotateBack(position, 0);
}
void Gun::setParent(bool _bool)
{
	hasParent = _bool;
}

void Gun::draw()
{
		if (!hasParent)
		{
			image->Draw(0, position.x, position.y);
		}
}

void Gun::load()
{
	image = new SpriteSheet(L"gun1.png", 20, 10, 0, 1, gfx);
}