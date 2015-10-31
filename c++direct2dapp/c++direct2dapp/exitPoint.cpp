#include "exitPoint.h"
#include "GameController.h"
#include "Level1.h"
#include "level2.h"

exitPoint::exitPoint(Point _position, float _width, float _height, int _timer, float _forcedxVel)
{
	position = _position;
	width = _width;
	height = _height;
	switchLevelTimer = _timer;
	activated = false;
	forcedxVel = _forcedxVel;
}
exitPoint::~exitPoint()
{
}
exitPoint::exitPoint() {}

void exitPoint::activate(Player* _pl)
{
	_pl->setInvulnerable(true);
	_pl->setxVel(forcedxVel);
	activated = true;
}
float exitPoint::getWidth()
{
	return width;
}
float exitPoint::getHeight()
{
	return height;
}
Point exitPoint::getPosition()
{
	return position;
}
void exitPoint::runTimer()
{
	if (activated)
	{
		switchLevelTimer--;
		if (switchLevelTimer <= 0)
		{
			gameController::SwitchLevel(new level2());
		}
	}
}