#pragma once
#include "rectangle.h"

class Platform : public Rect {
public:
	Platform();
	Platform(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	~Platform();
};
