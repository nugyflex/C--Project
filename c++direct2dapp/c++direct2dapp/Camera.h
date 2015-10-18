#pragma once
#include "gameLevel.h"

class Camera
{
	Point position;
	int width;
	int height;
	float yVel;
	float xVel;
	bool fixed;
public:
	Camera(Point _position);
	~Camera();
	float getY();
	float getX();
	Point getPosition();
	float getyVel();
	float getxVel();
	void setyVel(float _yVel);
	void setxVel(float _xVel);
	void setPosition(Point _position);
	void setX(float _x);
	void setY(float _y);
	void calcNewPos(Point _position);
};