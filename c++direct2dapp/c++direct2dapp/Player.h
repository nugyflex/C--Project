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
	int health;
	bool invulnerable;
	bool crouched;
	bool lastCrouched;
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
	void subtractHealth(int _amount);
	int getHealth();
	bool getInvulnerable();
	void setInvulnerable(bool _b);
	bool getCrouched();
	void setCrouched(bool _bool);
};