#include "Particle.h"

Particle::Particle(Point _position)
{
	xVel = 0;
	yVel = 0;
}
Particle::~Particle(){}

Particle::Particle(){}

void Particle::calcNewPos()
{
	if (hasGravity)
	{
		yVel += gravity;
	}
	position.x += xVel;
	position.y += yVel;
	despawnTimer--;
}

void Particle::draw()
{
	image->Draw(0, position.x, position.y);
}

void Particle::load(){}

int Particle::getDespawnTimer()
{
	return despawnTimer;
}

Point Particle::getPosition()
{
	return position;
}