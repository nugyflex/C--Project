#pragma once
#include "rectangle.h"

class Player: public Rect {

public:

	Player(Point _position, int _width, int _height, float _yVel, float _xVel, bool _fixed, Graphics *gfx);
	~Player();
 };