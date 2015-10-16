#include "gun.h"
#include "CollisionDetection.h"
#include <math.h>
Point mousePos;
Point cameraPos;
bool mouseLeft;
bool lastMouseLeft;
bool paused;

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
	Point thing = CollisionDetection::getClosestTarget(_position, mousePos);
	if (firing)
	{
		gfx->DrawLine(Rects[0]->getPosition(), CollisionDetection::getClosestTarget(Rects[0]->getPosition(), CollisionDetection::projectLineToEdge(cameraPos, 1280, 720, Rects[0]->getPosition(), mousePos)), 1, 0.85, 0.6, 1);
		//hitMarker->Draw(0, CollisionDetection::getClosestTarget(Rects[0]->getPosition(), CollisionDetection::projectLineToEdge(cameraPos, 1280, 720, Rects[0]->getPosition(), mousePos)).x - 4.5, CollisionDetection::getClosestTarget(Rects[0]->getPosition(), CollisionDetection::projectLineToEdge(cameraPos, 1280, 720, Rects[0]->getPosition(), mousePos)).y - 4.5);
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
	image = new SpriteSheet(L"gun1.png", 20, 10, 0, 1, gfx);
	hitMarker = new SpriteSheet(L"hitmarker.png", 9, 9, 0, 1, gfx);
	maxCooldown = 20;
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