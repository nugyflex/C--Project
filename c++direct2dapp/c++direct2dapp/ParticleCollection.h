#pragma once
#include "sparkParticle.h"
#include <vector>

using std::vector;

enum particleType { spark, fire };

class particleCollection
{

public:
	vector<Particle*> particles;
	particleCollection(Graphics* _gfx);
	~particleCollection();
	void add(particleType _type, Point _position);
	void draw();
	void manage();
protected:
	Graphics* gfx;
};