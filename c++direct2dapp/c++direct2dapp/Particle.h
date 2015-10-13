#pragma once
#include "SpriteSheet.h"
class Particle
{



public:
	Particle();
	Particle(Point _position);
	~Particle();
	virtual void draw();
	void calcNewPos();
	virtual void load();
	SpriteSheet* image;
	int getDespawnTimer();
	Point getPosition();

protected:
	Graphics* gfx;
	bool hasGravity;
	float gravity;
	int despawnTimer;
	Point position;
	float xVel;
	float yVel;
	
};