#pragma once

#include "SpriteSheet.h"
#include <vector>
#include "gun.h"

class Player : public Rect {
	SpriteSheet* spritewalkingleft;
	SpriteSheet* spritewalkingright;
	SpriteSheet* spritestandingleft;
	SpriteSheet* spritestandingright;
	SpriteSheet* spritewalkingleftwithbags;
	SpriteSheet* spritewalkingrightwithbags;
	SpriteSheet* spritestandingleftwithbags;
	SpriteSheet* spritestandingrightwithbags;
	bool hasBags;
public:
	Player();
	Player(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	~Player();
	void load() override;
	void draw() override;
	int lastdirection;
	int getWeaponOffsetY() override;
	int getWeaponOffsetX() override;
	vector<Gun*> weapons;
	void addWeapon(Gun* _gun);
	Point getWeaponPos();
	int weaponInUse;
	int getWeaponInUse();
};