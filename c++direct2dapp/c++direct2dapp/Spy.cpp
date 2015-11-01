#include "Spy.h"
#include "stdio.h"
#include <math.h>
#include "CollisionDetection.h"

Spy::Spy() {}

Spy::Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi) :
	Drone(_position, _width, _height, _yVel, _xVel, gfxi)
{
	mode = inactive;
}
Spy::Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Point _p1, Point _p2, Graphics * gfxi) :
	Drone(_position, _width, _height, _yVel, _xVel, _p1, _p2, gfxi)
{
	patrolDestinations.push_back(_p1);
	patrolDestinations.push_back(_p2);
	mode = patrol;
}

Spy::~Spy()
{
	delete up;
	delete down;
	delete left;
	delete right;
}
void Spy::load()
{
	left = new SpriteSheet(L"spy_left.png", 16, 8, 0, 1, gfx);
	right = new SpriteSheet(L"spy_right.png", 16, 8, 0, 1, gfx);
	up = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
	down = new SpriteSheet(L"spy_down.png", 8, 16, 0, 1, gfx);
	normal = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
	width = 8;
	height = 8;
	health = 4;
	speed = 1.8;
	hovermode = rise;
	laserColour = blue;
	roamTimer = 0;
	destinations.push_back(Point{ position.x, position.y });
	nextPatrolIndex = 0;
	maxShootCooldown = 30;
}