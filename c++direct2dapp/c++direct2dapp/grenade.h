#pragma once
#include "rectangle.h"
#include "SpriteSheet.h"
class Grenade: public Rect {
	int timer;
	Point lastposition;
	SpriteSheet* image;
public:
	Grenade();
	Grenade(Point _position, float _yVel, float _xVel, int _timer, Graphics * gfxi);
	~Grenade();
	void load() override;
	void draw() override;
	void calcNewPos() override;
	int getTimer();

};