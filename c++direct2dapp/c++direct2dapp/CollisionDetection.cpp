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
	if (_player->getX() + _player->getWidth() >= _platform->getX()) {
		return true;

	}
	return false;
}

bool CollisionDetection::test2(Rect *_player, Rect *_platform) {
	if (_player->getX() >= _platform->getX()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test3(Rect *_player, Rect *_platform) {
	if (_player->getX() >= _platform->getX() + _platform->getWidth()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test4(Rect *_player, Rect *_platform) {
	if (_player->getX() + _player->getWidth() >= _platform->getX() + _platform->getWidth()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test5(Rect *_player, Rect *_platform) {
	if (_player->getY() >= _platform->getY()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test6(Rect *_player, Rect *_platform) {
	if (_player->getY() + _player->getHeight() >= _platform->getY()) {
		return true;
	}
	return false;
}

bool CollisionDetection::test7(Rect *_player, Rect *_platform) {
	if (_player->getY() + _player->getHeight() >= _platform->getY() + _platform->getHeight()) {
		return true;
	}
	return false;
}
bool CollisionDetection::test8(Rect *_player, Rect *_platform) {
	if (_player->getY() >= _platform->getY() + _platform->getHeight()) {
		return true;
	}
	return false;
}

int CollisionDetection::getSide(Rect *_player, Rect *_platform) {
	int result = -1;
	int testvar = 0;
	if (test1(_player, _platform))
	{
		testvar = testvar + 1;
	}
	if (test2(_player, _platform)) {
		testvar = testvar + 2;
	}
	if (test3(_player, _platform)) {
		testvar = testvar + 4;
	}
	if (test4(_player, _platform)) {
		testvar = testvar + 8;
	}
	if (test5(_player, _platform)) {
		testvar = testvar + 16;
	}
	if (test6(_player, _platform)) {
		testvar = testvar + 32;
	}
	if (test7(_player, _platform)) {
		testvar = testvar + 64;
	}
	if (test8(_player, _platform)) {
		testvar = testvar + 128;
	}
	switch (testvar)
	{
		//left = 1, bottom = 2, right = 3, top = 4
		// 0,1,1,1,1,0,0,1=121
	case 121:
		result = 2;
		break;
		//0,0,1,0,1,0,0,1=73
	case 73:
		result = 4;
		break;
		//0,1,1,0,1,0,1,1
	case 107:
		result = 3;
		break;
		//0,1,1,0,0,0,0,1
	case 97:
		result = 1;
		break;
		//0,0,1,0,0,0,1,1
	case 35:
		result = 4;
		break;
		//0,0,1,1,0,0,0,1
	case 49:
		result = 1;
		break;
		//0,0,1,1,1,0,1,1 = 59
	case 59:
		result = 3;
		break;
		//0,1,1,1,0,0,1,1 = 115
	case 115:
		result = 2;
		break;
		//top left corner
		//0,0,1,0,0,0,0,1
	case 33:
		if ((_player->getX() + _player->getWidth()) - _platform->getX() > (_player->getY() + _player->getHeight()) - _platform->getY()) {
			result = 4;
		}
		else {
			result = 1;
		}
		break;

		//top right corner
		//0,0,1,0,1,0,1,1 = 43
	case 43:
		if (_platform->getX() + _platform->getWidth() - _player->getX() > (_player->getY() + _player->getHeight()) - _platform->getY()) {
			result = 4;

		}
		else {
			result = 3;

		}
		break;

		//bottom left corner
		//0,1,1,1,0,0,0,1 = 113
	case 113:
		if (_player->getX() + _player->getWidth() - _platform->getX() > _platform->getY() + _platform->getHeight() - _player->getY()) {

			result = 2;
		}
		else
		{
			result = 1;
		}
		break;

		//bottom right corner
		//0,1,1,1,1,0,1,1 = 123
	case 123:
		if (_platform->getX() + _platform->getWidth() - _player->getX() > _platform->getY() + _platform->getHeight() - _player->getY()) {
			result = 2;
		}
		else {
			result = 3;
		}
		break;
	}


	return result;
}
void CollisionDetection::correctPosition(Rect* _player, Rect* _platform) {
	if (!_player->getFixed())
	{
		switch (getSide(_player, _platform))
		{
		case 1:
			if (_player->getxVel() > 0) {
				_player->setxVel(0);
			}
			_player->setX(_platform->getX() - _player->getWidth() /*+ 1*/);
			break;
		case 3:
			if (_player->getxVel() < 0) {
				_player->setxVel(0);
			}
			_player->setX(_platform->getX() + _platform->getWidth() /*- 1*/);
			break;
		case 2:
			if (_player->getyVel() < 0) {
				_player->setyVel(0);
			}
			_player->setY(_platform->getY() + _platform->getHeight() /*- 1*/);
			break;
		case 4:
			if (_player->getyVel() > 0) {
				_player->setyVel(0);
			}
			_player->setY(_platform->getY() - _player->getHeight() /*+ 1*/);
			break;
		}
	}
}