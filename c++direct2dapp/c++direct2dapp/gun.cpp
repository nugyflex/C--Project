#include "gun.h"
#include "CollisionDetection.h"
#include <math.h>
Point mousePos;
Point cameraPos;
bool mouseLeft;
bool lastMouseLeft;
bool paused;
bool lastPaused;

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
	_position.x += _offSetX;
	_position.y += _offSetY;
	Point fireStart = { 0,0 };
	if (_position.x <= mousePos.x)
	{
		gfx->rotate(_position, (atan((mousePos.y - (_position.y)) / (mousePos.x - _position.x))));
		fireStart = { _position.x + 25 * (cos((atan((mousePos.y - (_position.y)) / (mousePos.x - _position.x))))), _position.y + 25 * (sin((atan((mousePos.y - (_position.y)) / (mousePos.x - _position.x))))) };
	}
	else
	{
		if (_position.y > mousePos.y)
		{
			gfx->flip(_position, (atan((mousePos.y + (2 * (_position.y - mousePos.y)) - (_position.y)) / (mousePos.x - _position.x))));
		}
		else
		{
			gfx->flip(_position, (atan((mousePos.y - (2 * (mousePos.y - _position.y)) - (_position.y)) / (mousePos.x - _position.x))));
		}
		fireStart = { _position.x - 25 * (cos((atan((mousePos.y - (_position.y)) / (mousePos.x - _position.x))))), _position.y - 25 * (sin((atan((mousePos.y - (_position.y)) / (mousePos.x - _position.x))))) };
	}
	image->Draw(0, 0, -1 * image->getFrameHeight() / 2);
	gfx->rotateBack(position, 0);
	Point thing = CollisionDetection::getClosestTarget(_position, mousePos);

	if (firing)
	{
		gfx->DrawLine(fireStart, CollisionDetection::getClosestTarget(_position, CollisionDetection::projectLineToEdge(cameraPos, _position, mousePos)), 1, 0.85, 0.6, 1);
		if (CollisionDetection::getClosestTarget(_position, CollisionDetection::projectLineToEdge(cameraPos, _position, mousePos)).x == 0)
		{
			int y = 0;
		}
		if (CollisionDetection::getClosestTarget(_position, CollisionDetection::projectLineToEdge(cameraPos, _position, mousePos)).y == 0)
		{
			int y = 0;
		}
	}
	firing = false;
	coolDown--;
}
bool Gun::fire()
{
	if (coolDown < 0)
	{
		firing = true;
		coolDown = maxCooldown;
		return true;
	}
	return false;
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
	image = new SpriteSheet(L"scar-h.png", 25, 8, 0, 1, gfx);
	hitMarker = new SpriteSheet(L"hitmarker.png", 9, 9, 0, 1, gfx);
	maxCooldown = 5;
	coolDown = 0;
}

bool Gun::getFiring()
{
	return firing;
}

int Gun::getCooldown()
{
	return coolDown;
}