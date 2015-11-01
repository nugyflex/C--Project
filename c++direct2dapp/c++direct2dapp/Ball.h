#pragma once
#include "Graphics.h"
#include "CollisionDetection.h"

class Ball
{
	Point center;
	int radius;
	float yVel;
	float xVel;
protected:
	Graphics *gfx;

public:

	Ball(Point _center, int _radius, float _yVel, float _xVel, Graphics *gfx);
	~Ball();
	void setRadius(int _radius);
	int getRadius();
	float getY();
	float getX();
	void changeY(float _yChange);
	void changeX(float _xChange);
	float getyVel();
	float getxVel();
	void setyVel(float _yVel);
	void setxVel(float _xVel);
	void setPosition(Point _center);
	void setX(float _x);
	void setY(float _y);

	void calcNewPos();

	void draw();
};
