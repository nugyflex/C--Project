#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"


class Gun
{
	Point position;
	SpriteSheet* image;
	float rotation = 0;

public:
	Gun(float _x, float _y, Graphics * gfx);
	~Gun();
	void load();
	void draw();
	bool hasParent;
	void setParent(bool _bool);
	void calcNewPos();
	float xVel;
	float yVel;
	void drawOnParent(Point _position, int _offSetX, int  _offSetY);
protected:
	Graphics* gfx;

};
