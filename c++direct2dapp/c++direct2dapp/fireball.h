#pragma once
#pragma once
#include "rectangle.h"
#include "SpriteSheet.h"

class FireBall : public Rect {
	SpriteSheet* mainsprite;
public:
	FireBall();
	FireBall(Point _position, float _yVel, float _xVel, Graphics * gfxi);
	~FireBall();
	void load() override;
	void draw() override;
};