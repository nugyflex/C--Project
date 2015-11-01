#pragma once
#pragma once
#include "drone.h"
#include "SpriteSheet.h"

class Hunter : public Drone {
public:
	Hunter();
	Hunter(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	Hunter(Point _position, float _width, float _height, float _yVel, float _xVel, Point _p1, Point _p2, Graphics * gfxi);
	~Hunter();
	virtual void load() override;
	virtual void draw() override;
};