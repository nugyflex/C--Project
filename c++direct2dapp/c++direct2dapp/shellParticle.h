#pragma once
#include "Particle.h"

class shellParticle : public Particle
{
	int frame;
	float rotation;
public:
	shellParticle(Point _position, Graphics* gfx, float _xvel, float _yvel);
	~shellParticle();
	void load() override;
	void draw() override;
};