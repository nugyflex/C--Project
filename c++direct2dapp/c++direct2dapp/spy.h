#pragma once
#pragma once
#include "drone.h"
#include "SpriteSheet.h"

class Spy : public Drone {
public:
	Spy();
	Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Point _p1, Point _p2, Graphics * gfxi);
	~Spy();
	virtual void load() override;
};