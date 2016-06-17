#pragma once
#include "drone.h"
class explosion
{
private:
	float damage;
	int range;
	Point position;
public:
	explosion(int _range, float _damage, Point _position);
	~explosion();
	void doDamage();
};