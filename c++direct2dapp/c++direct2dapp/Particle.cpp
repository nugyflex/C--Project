#include "Particle.h"

Particle::Particle(Point _position)
{
	xVel = 0;
	yVel = 0;
}
Particle::~Particle() { delete image; }

Particle::Particle() {}

void Particle::calcNewPos()
{
	if (hasGravity)
	{
		yVel += gravity;
	}
	if (yVel > maxvel)
	{
		yVel = maxvel;
	}
	position.x += xVel;
	position.y += yVel;
	despawnTimer--;

	if (floor(xVel * 10) > 0)
	{
		xVel -= 0.05;
	}
	if (floor(xVel * 10) < 0)
	{
		xVel += 0.05;
	}
	if (xVel < 0.06 && xVel > -0.06)
	{
		xVel = 0;
	}
}

void Particle::draw()
{
	image->Draw(0, position.x, position.y);
}

void Particle::load() {}

int Particle::getDespawnTimer()
{
	return despawnTimer;
}

Point Particle::getPosition()
{
	return position;
}

int Particle::getHeight()
{
	return height;
}

int Particle::getWidth()
{
	return width;
}

void Particle::setX(float _x) {
	position.x = _x;
}

void Particle::setY(float _y) {
	position.y = _y;
}

void Particle::setxVel(float _xvel) {
	xVel = _xvel;
}

void Particle::setyVel(float _yvel) {
	yVel = _yvel;
}

float Particle::getxVel() {
	return xVel;
}

float Particle::getyVel() {
	return yVel;
}