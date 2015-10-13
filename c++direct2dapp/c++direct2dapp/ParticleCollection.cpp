#include "ParticleCollection.h"
#include "CollisionDetection.h"

particleCollection::particleCollection(Graphics* _gfx)
{
	gfx = _gfx;
}
particleCollection::~particleCollection() {}
void particleCollection::add(particleType _type, Point _position)
{
	switch (_type)
	{
	case spark:
		particles.push_back(new sparkParticle(_position, gfx));
	}
	particles[particles.size() - 1]->load();
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
			particles.erase(particles.begin() + i);
		}
	}
	for (int i = 0; i < particles.size(); i++)
	{
		for (int j = 0; j < Rects.size(); j++)
		{
			if (CollisionDetection::checkPointRectIntersect(particles[i]->getPosition(), Rects[j]->getPosition(), Rects[j]->getWidth(), Rects[j]->getHeight()) && Rects[j]->getType() == platform)
			{
				particles.erase(particles.begin() + i);
				break;
			}
			if (CollisionDetection::checkPointRectIntersect(Point{ particles[i]->getPosition().x + 7, particles[i]->getPosition().y + 7 }, Rects[j]->getPosition(), Rects[j]->getWidth(), Rects[j]->getHeight()) && Rects[j]->getType() == platform)
			{
				particles.erase(particles.begin() + i);
				break;
			}
		}
	}
}