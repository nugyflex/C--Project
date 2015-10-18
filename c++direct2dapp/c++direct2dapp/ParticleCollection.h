#pragma once
#include "sparkParticle.h"
#include "SmokeParticle.h"
#include <vector>

using std::vector;

enum particleType { spark, fire, smoke };

class particleCollection
{

public:
	vector<Particle*> particles;
	particleCollection(Graphics* _gfx);
	~particleCollection();
	void add(particleType _type, Point _position, float _xvel, float _yvel);
	void draw();
	void manage();
protected:
	Graphics* gfx;
};