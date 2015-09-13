#pragma once
#include "rectangle.h"
#include "SpriteSheet.h"

class Player: public Rect {
	SpriteSheet* spritewalkingleft;
	SpriteSheet* spritewalkingright;
public:
	Player();
	Player(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics * gfxi);
	~Player();
	void load() override;
	void draw() override;
 };