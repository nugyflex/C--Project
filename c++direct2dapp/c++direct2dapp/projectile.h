#pragma once
#include "Graphics.h"
class projectile
{
public:
	projectile();
	projectile(Point _position, float _xVel, float _yVel, Graphics* _gfx);
	projectile(Point _position, float _xVel, float _yVel, colour _c, Graphics* _gfx);
	~projectile();
	virtual void draw();
	void calcNewPos();
	Point getPosition();
	float getxVel();
	float getyVel();
	Point getLastPosition();
	void setxVel(float _x);
	void setyVel(float _y);
	float getSpeed();
	float getAngle();
protected:
	Graphics* gfx;
	float gravity;
	Point position;
	Point lastPosition1;
	Point lastPosition2;
	float xVel;
	float yVel;
	float speed;
	float angle;
	float cr;
	float cg;
	float cb;
};