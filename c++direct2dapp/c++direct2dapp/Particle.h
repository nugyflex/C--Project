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
	int getWidth();
	int getHeight();
	void setyVel(float _yVel);
	void setxVel(float _xVel);
	void setX(float _x);
	void setY(float _y);
	float getxVel();
	float getyVel();

protected:
	Graphics* gfx;
	bool hasGravity;
	float gravity;
	int despawnTimer;
	Point position;
	float xVel;
	float yVel;
	int width;
	int height;
	float maxvel;
};