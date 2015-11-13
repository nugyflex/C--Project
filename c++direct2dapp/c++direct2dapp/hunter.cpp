#include "hunter.h"
#include "stdio.h"
#include <math.h>
#include "CollisionDetection.h"

Hunter::Hunter() {}

Hunter::Hunter(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi) :
	Drone(_position, _width, _height, _yVel, _xVel, gfxi)
{
	mode = inactive;
}
Hunter::Hunter(Point _position, float _width, float _height, float _yVel, float _xVel, Point _p1, Point _p2, Graphics * gfxi) :
	Drone(_position, _width, _height, _yVel, _xVel, _p1, _p2, gfxi)
{
	patrolDestinations.push_back(_p1);
	patrolDestinations.push_back(_p2);
	mode = patrol;
}

Hunter::~Hunter()
{
	delete up;
	delete down;
	delete left;
	delete right;
}
void Hunter::load()
{
	left = new SpriteSheet(L"hunter_left.png", 60, 32, 0, 1, gfx);
	right = new SpriteSheet(L"hunter_right.png", 60, 32, 0, 1, gfx);
	up = new SpriteSheet(L"hunter_up.png", 60, 32, 0, 1, gfx);
	down = new SpriteSheet(L"hunter_down.png", 60, 32, 0, 1, gfx);
	normal = new SpriteSheet(L"hunter_up.png", 60, 32, 0, 1, gfx);
	default = new SpriteSheet(L"hunter_default.png", 60, 32, 0, 1, gfx);
	width = 44;
	height = 12;
	health = 10;
	speed = 1;
	hovermode = rise;
	laserColour = red;
	roamTimer = 0;
	destinations.push_back(Point{ position.x, position.y });
	nextPatrolIndex = 0;
	maxShootCooldown = 10;
	type = hunterDrone;
}
void Hunter::draw()
{
	default->Draw(0, position.x - 8, position.y - 6);
	if (yVel < 0)
	{
		up->Draw(0, position.x - 8, position.y - 6);
	}
	if (yVel >= 0)
	{
		down->Draw(0, position.x - 8, position.y - 6);
	}
	if (xVel < 0)
	{
		left->Draw(0, position.x - 8, position.y - 6);
	}
	if (xVel > 0)
	{
		right->Draw(0, position.x - 8, position.y - 6);
	}
	firing = false;
	shootCooldown--;
}