#pragma once
#include "rectangle.h"

class Platform : public Rect {

public:
	Platform();
	Platform(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics * gfxi);
	~Platform();
};
