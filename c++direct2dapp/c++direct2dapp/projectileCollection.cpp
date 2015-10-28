#include "projectileCollection.h"
#include "Player.h"

projectileCollection::projectileCollection(Graphics* _gfx)
{
	gfx = _gfx;
}
projectileCollection::~projectileCollection() {}
void projectileCollection::add(Point _position, float _xvel, float _yvel)
{
	projectiles.push_back(new projectile(_position, _xvel, _yvel, gfx));
}
void projectileCollection::add(Point _position, Point _p2, float _speed)
{
	float speed = _speed;
	float theta = atan(-1 * (_p2.y - _position.y) / (_p2.x - _position.x));
	if (_p2.x > _position.x) {
		projectiles.push_back(new projectile(_position, cos(theta) * speed, sin(theta) * -1 * speed, gfx));
	}
	else {
		projectiles.push_back(new projectile(_position, cos(theta) * -1 * speed, sin(theta) * speed, gfx));
	}
}
void projectileCollection::draw()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->draw();
	}
}
void projectileCollection::manage()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->calcNewPos();

		for (int j = 0; j < Rects.size(); j++)
		{
			if (Rects[j]->getType() == platform)
			{
				if (CollisionDetection::checkRectLineIntersect(Rects[j]->getPosition(), Rects[j]->getWidth(), Rects[j]->getHeight(), projectiles[i]->getPosition(), projectiles[i]->getLastPosition()))
				{
					projectiles.erase(projectiles.begin() + i);
					break;
				}
			}
			if (Rects[j]->getType() == player)
			{
				if (CollisionDetection::checkRectLineIntersect(Rects[j]->getPosition(), Rects[j]->getWidth(), Rects[j]->getHeight(), projectiles[i]->getPosition(), projectiles[i]->getLastPosition()))
				{
					((Player*)Rects[j])->subtractHealth(1);
					projectiles.erase(projectiles.begin() + i);
					break;
				}
			}
		}

	}
}