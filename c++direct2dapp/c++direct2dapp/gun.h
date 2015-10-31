#pragma once
#include "ParticleCollection.h"
#include "projectileCollection.h"
#include "Graphics.h"
#include "SpriteSheet.h"
#include "rectangle.h"

class Gun
{
	Point position;
	SpriteSheet* image;
	SpriteSheet* hitMarker;
	float rotation = 0;
	bool firing;
	int maxCooldown;
	int coolDown;
public:
	Gun(float _x, float _y, Graphics * gfx);
	~Gun();
	bool getFiring();
	void load();
	void draw();
	bool fire();
	bool hasParent;
	void setParent(bool _bool);
	void calcNewPos();
	float xVel;
	float yVel;
	int getCooldown();
	void drawOnParent(Point _position, int _offSetX, int  _offSetY);
protected:
	Graphics* gfx;
};
