#pragma once
#include "Graphics.h"
#include <string.h>
using namespace std;

enum rectType { platform, player, fireball };

class Rect
{


protected:
	Point position;
	float width;
	float height;
	float yVel;
	float xVel;
	bool fixed;
	rectType type;
	Graphics *gfx;

public:
	Rect();
	Rect(Point _position, float _width, float _height, float _yVel, float _xVel, bool _fixed, rectType _type, Graphics * gfxi);
	~Rect();

	float getWidth();
	float getHeight();
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
	void setWidth(float _width);
	void setHeight(float _height);
	bool getFixed();
	void calcNewPos();
	void gravity(float _g);
	rectType getType();

	virtual void draw();

	virtual void load();

};