#pragma once
#include "projectile.h"
#include "CollisionDetection.h"
#include <vector>

using std::vector;

class projectileCollection
{
public:
	vector<projectile*> projectiles;
	projectileCollection(Graphics* _gfx);
	~projectileCollection();
	void add(Point _position, float _xvel, float _yvel);
	void add(Point _position, Point _position2, float _speed);
	void add(Point _position, Point _position2, float _speed, colour _c);
	void draw();
	void manage();
	void manageTracking(Point _p);
protected:
	Graphics* gfx;
};