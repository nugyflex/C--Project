#include "ParticleCollection.h"
#include "CollisionDetection.h"

particleCollection::particleCollection(Graphics* _gfx)
{
	gfx = _gfx;
}
particleCollection::~particleCollection() {
	for (int i = 0; i < particles.size(); i++)
	{
		delete particles[i];
	}
}
void particleCollection::add(particleType _type, Point _position, float _xvel, float _yvel)
{
	switch (_type)
	{
	case spark:
		particles.push_back(new sparkParticle(_position, gfx, _xvel, _yvel));

		break;
	case smoke:
		particles.push_back(new smokeParticle(_position, gfx));
		break;
	case shell:
		particles.push_back(new shellParticle(_position, gfx, _xvel, _yvel));
		break;
	}

	particles[particles.size() - 1]->load();
	for (int i = 0; i < Rects.size(); i++)
	{
		CollisionDetection::correctPositionParticle(particles[particles.size() - 1], Rects[i]);
	}
}
void particleCollection::add(particleType _type, Point _position)
{
	switch (_type)
	{
	case smoke:
		particles.push_back(new smokeParticle(_position, gfx));
		break;
	}

	particles[particles.size() - 1]->load();
	for (int i = 0; i < Rects.size(); i++)
	{
		CollisionDetection::correctPositionParticle(particles[particles.size() - 1], Rects[i]);
	}
}
void particleCollection::draw()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->draw();
	}
}
void particleCollection::manage()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->calcNewPos();
	}
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->getDespawnTimer() <= 0)
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
	for (int i = 0; i < particles.size(); i++)
	{
		for (int j = 0; j < Rects.size(); j++)
		{
			if (Rects[j]->getType() == platform)
			{
				CollisionDetection::correctPositionParticle(particles[i], Rects[j]);
			}
		}
		/*//uncomment if you want performance issues
		for (int j = 0; j < particles.size(); j++)
		{
			CollisionDetection::correctPositionParticle(particles[i], new Rect(particles[j]->getPosition(), particles[j]->getWidth(), particles[j]->getHeight(), 0, 0, false, player, false, gfx));
		}*/
	}
}