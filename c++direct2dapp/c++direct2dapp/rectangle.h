#pragma once
#include "Graphics.h"
#include "GameLevel.h"
#include "CollisionDetection.h"

class Rect
{
	Point position;
	int width;
	int height;
	float yVel;
	float xVel;
protected:
	Graphics *gfx;

public:


	Rect(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics *gfx);
	~Rect();

	int getWidth();
	int getHeight();
	float getY();
	float getX();
	Point getPosition();
	void changeY(float _yChange);
	void changeX(float _xChange);
	float getyVel();
	float getxVel();
	void setyVel(float _yVel);
	void setxVel(float _xVel);
	void setPosition(Point _position);
	void setX(float _x);
	void setY(float _y);
	void setWidth(int _width);
	void setHeight(int _height);

	void calcNewPos();

	void draw();



};

