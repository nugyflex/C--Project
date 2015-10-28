#pragma once
#include "Graphics.h"
class projectile
{

public:
	projectile();
	projectile(Point _position, float _xVel, float _yVel, Graphics* _gfx);
	~projectile();
	virtual void draw();
	void calcNewPos();
	Point getPosition();
	float getxVel();
	float getyVel();
	Point getLastPosition();

protected:
	Graphics* gfx;
	float gravity;
	Point position;
	Point lastPosition1;
	Point lastPosition2;
	float xVel;
	float yVel;
};