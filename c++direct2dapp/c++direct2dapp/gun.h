#pragma once
#include "ParticleCollection.h"
#include "projectileCollection.h"
#include "Graphics.h"
#include "SpriteSheet.h"
#include "rectangle.h"

class Gun
{
public:
	Gun(float _x, float _y, Graphics * gfx);
	~Gun();
	Gun();
	bool getFiring();
	float getDamage();
	virtual void load();
	void draw();
	bool fire();
	bool hasParent;
	void setParent(bool _bool);
	void calcNewPos();
	float xVel;
	float yVel;
	int getCooldown();
	void drawOnParent(Point _position, int _offSetX, int  _offSetY);
	void setFireLatch(bool _bool);
	bool getLatch();
	bool getCanFire();
protected:
	Graphics* gfx;
	Point position;
	SpriteSheet* image;
	SpriteSheet* hitMarker;
	float rotation = 0;
	bool firing;
	int maxCooldown;
	int coolDown;
	float damage;
	bool fireLatch;
	bool hasLatch;
	int width;
	int height;
};
