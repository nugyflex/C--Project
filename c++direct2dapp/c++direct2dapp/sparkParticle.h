#pragma once
#include "Particle.h"

class sparkParticle : public Particle
{
public:
	sparkParticle(Point _position, Graphics* gfx);
	~sparkParticle();
	void load() override;
	void draw() override;
};