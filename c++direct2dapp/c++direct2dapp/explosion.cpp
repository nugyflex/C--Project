#include "explosion.h"
#include "CollisionDetection.h"

explosion::explosion(int _range, float _damage, Point _position)
{
	position = _position;
	damage = _damage;
	range = _range;
	doDamage();
}
explosion::~explosion(){}
void explosion::doDamage()
{
	for (int i = 0; i < Rects.size(); i++)
	{
		if (Rects[i]->getType() == drone && CollisionDetection::finddistance(position.x, position.y, Rects[i]->getPosition().x, Rects[i]->getPosition().y) < range)
		{
			((Drone*)Rects[i])->subtractHealth(damage);
		}
	}
}