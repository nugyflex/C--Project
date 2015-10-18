#pragma once
#include "Particle.h"

class sparkParticle : public Particle
{
	int frame;
public:
	sparkParticle(Point _position, Graphics* gfx, float _xvel, float _yvel);
	~sparkParticle();
	void load() override;
	void draw() override;
};