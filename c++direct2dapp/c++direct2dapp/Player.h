#pragma once
#include "rectangle.h"
#include "SpriteSheet.h"

class Player: public Rect {
	SpriteSheet* spritewalkingleft;
	SpriteSheet* spritewalkingright;
	SpriteSheet* spritestandingleft;
	SpriteSheet* spritestandingright;
	SpriteSheet* spritejumpingleft;
	SpriteSheet* spritejumpingright;
public:
	Player();
	Player(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	~Player();
	void load() override;
	void draw() override;
	int lastdirection;
};