#include "gun.h"
#include "CollisionDetection.h"
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
	if (_position.x <= mousePos.x)
	{
		gfx->rotate(_position, (atan((mousePos.y - (_position.y)) / (mousePos.x - _position.x))));
	}
	else
	{
		if (_position.y > mousePos.y)
		{
			gfx->flip(_position, (atan((mousePos.y+(2*(_position.y-mousePos.y)) - (_position.y)) / (mousePos.x - _position.x))));
		}
		else
		{
			gfx->flip(_position, (atan((mousePos.y - (2 * (mousePos.y - _position.y)) - (_position.y)) / (mousePos.x - _position.x))));
		}
	}
	image->Draw(0, 0, -1*image->getFrameHeight()/2);
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