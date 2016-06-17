#include "exitPoint.h"
#include "GameController.h"
#include "Level1.h"
#include "level2.h"
#include "level3.h"

exitPoint::exitPoint(Point _position, float _width, float _height, int _timer, float _forcedxVel, int _level)
{
	position = _position;
	width = _width;
	height = _height;
	switchLevelTimer = _timer;
	activated = false;
	forcedxVel = _forcedxVel;
	level = _level;
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
			switch (level)
			{
			case 1:
				gameController::SwitchLevel(new Level1());
				break;
			case 2:
				gameController::SwitchLevel(new level2());
				break;
			case 3:
				gameController::SwitchLevel(new Level3());
			}
		}
	}
}
float exitPoint::getForcedxVel()
{
	return forcedxVel;
}
int exitPoint::getLevel()
{
	return level;
}
int exitPoint::getTimer()
{
	return switchLevelTimer;
}
vector<exitPoint*> exitPoints;