#pragma once
#include "Player.h"

class exitPoint //the Rect class, inherited by fireball, spy, player, and platform
{
protected:
	Point position;
	float width;
	float height;
	float forcedxVel;
	int switchLevelTimer;
	bool activated;
public:
	exitPoint();
	exitPoint(Point _position, float _width, float _height, int _timer, float _forcedxVel);
	~exitPoint();
	float getWidth();
	float getHeight();
	Point getPosition();
	void runTimer();
	void activate(Player* _pl);
};
