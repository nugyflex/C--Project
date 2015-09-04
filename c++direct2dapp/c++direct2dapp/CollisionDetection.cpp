#include "CollisionDetection.h"


bool CollisionDetection::CheckRectangleIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{

	if (x2 >x3&&x1<x4&&y2>y3&&y1 < y4)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

int CollisionDetection::finddistance(float x1, float y1, float x2, float y2)
{
	float ob1ymob2y = pow((y1 - y2), 2);
	float ob2ymob1y = pow((y2 - y1), 2);
	float ob1xmob2x = pow((x1 - x2), 2);
	float ob2xmob1x = pow((x2 - x1), 2);
	if (x1 > x2) {
		if (y1 > y2) {
			return sqrt(ob1ymob2y + ob1xmob2x);

		}
		if (y1 < y2) {
			return sqrt(ob2ymob1y + ob1xmob2x);

		}
	}
	if (x1 < x2) {
		if (y1 > y2) {
			return sqrt(ob1ymob2y + ob2xmob1x);
		}
		if (y1 < y2) {
			return sqrt(ob2ymob1y + ob2xmob1x);
		}
	}
}
bool CollisionDetection::test1(Rect *_player, Rect *_platform) {
	if (_player->getX() + _player->getWidth() > _platform->getX()) {
		return true;

	}
	return false;
}

bool CollisionDetection::test2(Rect *_player, Rect *_platform) {
	if (_player->getX() > _platform->getX()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test3(Rect *_player, Rect *_platform) {
	if (_player->getX() > _platform->getX() + _platform->getWidth()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test4(Rect *_player, Rect *_platform) {
	if (_player->getX() + _player->getWidth() > _platform->getX() + _platform->getWidth()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test5(Rect *_player, Rect *_platform) {
	if (_player->getY() > _platform->getyVel()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test6(Rect *_player, Rect *_platform) {
	if (_player->getY() + _player->getHeight() > _platform->getY()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test7(Rect *_player, Rect *_platform) {
	if (_player->getY() + _player->getHeight() > _platform->getY() + _platform->getHeight()) {
		return true;
	}
	return false;
}
bool CollisionDetection::test8(Rect *_player, Rect *_platform) {
	if (_player->getY() > _platform->getY() + _platform->getHeight()) {
		return true;
	}
	return false;
}