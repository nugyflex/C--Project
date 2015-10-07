#pragma once
#include "Common.h"
#include "CollisionDetection.h"

class Beam
{
	Point p1;
	Point p2;
	vector<Rect*> &Rects;
public:
	Beam::Beam(Point _p1, Point _p2, vector<Rect*> &_Rects);
	~Beam();
	void aim(Point _p1, Point _p2);
	void  damageEnemies(float _damage);
};