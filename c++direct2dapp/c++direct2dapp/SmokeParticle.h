#pragma once
#pragma once
#include "Particle.h"

class smokeParticle : public Particle
{
	int frame;
public:
	smokeParticle(Point _position, Graphics* gfx);
	~smokeParticle();
	void load() override;
	void draw() override;
};