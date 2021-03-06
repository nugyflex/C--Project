#include "CollisionDetection.h"

bool CollisionDetection::CheckRectangleIntersect(Rect *_ob1, Point _p1, int _width, int _height)
{
	if (_ob1->getX() + _ob1->getWidth() > _p1.x && _ob1->getX() < _p1.x + _width && _ob1->getY() + _ob1->getHeight() > _p1.y && _ob1->getY() < _p1.y + _height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionDetection::CheckRectangleIntersect(Rect *_ob1, Rect *_ob2)
{
	if (_ob1->getX() + _ob1->getWidth() > _ob2->getX() && _ob1->getX() < _ob2->getX() + _ob2->getWidth() && _ob1->getY() + _ob1->getHeight() > _ob2->getY() && _ob1->getY() < _ob2->getY() + _ob2->getHeight())
	{
		return true;
	}
	else
	{
		return false;
	}
}

float CollisionDetection::finddistance(float x1, float y1, float x2, float y2)
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
//this function corrects the position of a rectangle if it is colliding with another rectangle
void CollisionDetection::correctPosition(Rect* _player, Rect* _platform) {
	//left = 1, bottom = 2, right = 3, top = 4
	if (!_player->getFixed() && CheckRectangleIntersect(_player, _platform))
	{
		switch (getSide(_player, _platform))
		{
		case 1:
			if (_player->getxVel() > 0) {
				_player->setxVel(0);
			}
			_player->setX(_platform->getX() - _player->getWidth());
			break;
		case 3:
			if (_player->getxVel() < 0) {
				_player->setxVel(0);
			}
			_player->setX(_platform->getX() + _platform->getWidth());
			break;
		case 2:
			if (_player->getyVel() < 0) {
				_player->setyVel(0);
			}
			_player->setY(_platform->getY() + _platform->getHeight());
			break;
		case 4:
			if (_player->getyVel() > 0) {
				_player->setyVel(0);
			}
			_player->setY(_platform->getY() - _player->getHeight());
			break;
		}
	}
}
void CollisionDetection::correctPositionParticle(Particle* _particle, Rect* _platform) {
	//left = 1, bottom = 2, right = 3, top = 4
	Rect* _player = new Rect(_particle->getPosition(), _particle->getWidth(), _particle->getHeight(), 0, 0, false, player, false, new Graphics);
	if (!_player->getFixed() && CheckRectangleIntersect(_player, _platform))
	{
		switch (getSide(_player, _platform))
		{
		case 1:
			if (_particle->getxVel() > 0) {
				_particle->setxVel(0);
			}
			_particle->setX(_platform->getX() - _particle->getWidth());
			break;
		case 3:
			if (_particle->getxVel() < 0) {
				_particle->setxVel(0);
			}
			_particle->setX(_platform->getX() + _platform->getWidth());
			break;
		case 2:
			if (_particle->getyVel() < 0) {
				_particle->setyVel(0);
			}
			_particle->setY(_platform->getY() + _platform->getHeight());
			break;
		case 4:
			if (_particle->getyVel() > 0) {
				_particle->setyVel(_particle->getyVel()*-0.5);
			}
			_particle->setY(_platform->getY() - _particle->getHeight());
			break;
		}
	}
	delete _player;
}
bool CollisionDetection::isBetween(float _1, float _2, float _3)
{
	//tollerance
	/*
	_1 = floor(_1 * 10) / 10;
	_2 = floor(_2 * 10) / 10;
	_3 = floor(_3 * 10) / 10;
	*/
	if (_3 == _2 || _3 == _1)
	{
		return true;
	}
	else
	{
		if (_1 > _2)
		{
			if (_3 > _2&&_3 < _1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (_3 < _2 && _3 > _1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
bool CollisionDetection::checkLineIntersect(Point _p1, Point _p2, Point _p3, Point _p4)
{
	if ((_p1.x - _p2.x)*(_p3.y - _p4.y) - (_p1.y - _p2.y)*(_p3.x - _p4.x) != 0)
	{
		if (isBetween(_p1.x, _p2.x, getLineIntersect(_p1, _p2, _p3, _p4).x)) {
			if (isBetween(_p3.x, _p4.x, getLineIntersect(_p1, _p2, _p3, _p4).x)) {
				if (isBetween(_p1.y, _p2.y, getLineIntersect(_p1, _p2, _p3, _p4).y)) {
					if (isBetween(_p3.y, _p4.y, getLineIntersect(_p1, _p2, _p3, _p4).y)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
Point CollisionDetection::getLineIntersect(Point _p1, Point _p2, Point _p3, Point _p4)
{
	float tempx = ((_p1.x*_p2.y - _p1.y*_p2.x)*(_p3.x - _p4.x) - (_p1.x - _p2.x)*(_p3.x*_p4.y - _p3.y*_p4.x)) / ((_p1.x - _p2.x)*(_p3.y - _p4.y) - (_p1.y - _p2.y)*(_p3.x - _p4.x));
	float tempy = ((_p1.x*_p2.y - _p1.y*_p2.x)*(_p3.y - _p4.y) - (_p1.y - _p2.y)*(_p3.x*_p4.y - _p3.y*_p4.x)) / ((_p1.x - _p2.x)*(_p3.y - _p4.y) - (_p1.y - _p2.y)*(_p3.x - _p4.x));
	if (_p1.y == _p2.y)
	{
		tempy = _p1.y;
	}
	else if (_p1.x == _p2.x)
	{
		tempx = _p1.x;
	}
	if (_p3.y == _p4.y)
	{
		tempy == _p3.y;
	}
	else if (_p3.x == _p4.x)
	{
		tempx = _p3.x;
	}

	Point tempPoint = { tempx, tempy };
	return tempPoint;
}

bool CollisionDetection::checkRectLineIntersect(Point _rp, float _width, float _height, Point _p1, Point _p2)
{
	Point p1 = _rp;
	Point p2 = { _rp.x + _width, _rp.y };
	Point p3 = { _rp.x + _width, _rp.y + _height };
	Point p4 = { _rp.x , _rp.y + _height };
	if (checkLineIntersect(p1, p2, _p1, _p2))
	{
		return true;
	}
	if (checkLineIntersect(p2, p3, _p1, _p2))
	{
		return true;
	}
	if (checkLineIntersect(p3, p4, _p1, _p2))
	{
		return true;
	}
	if (checkLineIntersect(p4, p1, _p1, _p2))
	{
		return true;
	}
	return false;
}
Point CollisionDetection::getClosestPoint(Point _p, vector<Point> _Points)
{
	vector< vector<int> > array(2, vector<int>(_Points.size()));
	float test = 0;
	for (int i = 0; i < _Points.size(); i++)
	{
		array[0][i] = finddistance(_p.x, _p.y, _Points[i].x, _Points[i].y);
		test = array[0][i];
		array[1][i] = i;
		test = array[1][i];
	}

	int currentmin = 1000000000;
	int currentmini = -1;
	//finding the index of the minimum
	for (int j = 0; j < _Points.size(); j++) {
		test = array[0][j];
		test = array[1][j];
		if (array[0][j] < currentmin) {
			currentmin = array[0][j];
			currentmini = j;
		}
	}
	int temp1 = _Points[array[1][currentmini]].x;
	temp1 = _Points[array[1][currentmini]].y;
	return _Points[array[1][currentmini]];
}

Point CollisionDetection::getClosestRectLineIntersect(Point _rp, float _width, float _height, Point _p1, Point _p2)
{
	Point p1 = _rp;
	Point p2 = { _rp.x + _width, _rp.y };
	Point p3 = { _rp.x + _width, _rp.y + _height };
	Point p4 = { _rp.x , _rp.y + _height };
	Point pp1;
	Point pp2;
	Point pp3;
	Point pp4;
	int array[2][4];

	for (int i = 0; i < 4; i++)
	{
		array[1][i] = i;
		array[0][i] = 100000;
	}
	if (checkLineIntersect(p1, p2, _p1, _p2))
	{
		pp1 = getLineIntersect(p1, p2, _p1, _p2);
		array[0][0] = finddistance(_p2.x, _p2.y, pp1.x, pp1.y);
	}
	if (checkLineIntersect(p2, p3, _p1, _p2))
	{
		pp2 = getLineIntersect(p2, p3, _p1, _p2);
		array[0][1] = finddistance(_p2.x, _p2.y, pp2.x, pp2.y);
	}
	if (checkLineIntersect(p3, p4, _p1, _p2))
	{
		pp3 = getLineIntersect(p3, p4, _p1, _p2);
		array[0][2] = finddistance(_p2.x, _p2.y, pp3.x, pp3.y);
	}
	if (checkLineIntersect(p4, p1, _p1, _p2))
	{
		pp4 = getLineIntersect(p4, p1, _p1, _p2);
		array[0][3] = finddistance(_p2.x, _p2.y, pp4.x, pp4.y);
	}

	int currentmin;
	int currentmini;
	for (int i = 0; i < 4; i++) {
		currentmin = 1000000000;
		currentmini = -1;

		for (int j = 0; j < 4; j++) {
			if (array[0][j] < currentmin) {
				currentmin = array[0][j];
				currentmini = j;
			}
		}
	}
	switch (currentmini)
	{
	case 0:
		return pp1;
		break;
	case 1:
		return pp2;
		break;
	case 2:
		return pp3;
		break;
	case 3:
		return pp4;
		break;
	}
}
Point CollisionDetection::getClosestTarget(Point _p1, Point _p2)
{
	_p2.x = floor(_p2.x);
	_p2.y = floor(_p2.y);
	_p1.x = floor(_p1.x);
	_p1.y = floor(_p1.y);
	vector<Point> temppoints;
	for (int i = 0; i < Rects.size(); i++)
	{
		if (Rects[i]->getType() != player)
		{
			if (checkRectLineIntersect(Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight(), _p2, _p1))
			{
				Point test = getClosestRectLineIntersect(Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight(), _p2, _p1);
				temppoints.push_back(test);
			}
		}
	}

	for (int i = 0; i < Rects.size(); i++)
	{
		if (Rects[i]->getType() != player)
		{
			if (checkRectLineIntersect(_p1, Rects[i]->getWidth(), Rects[i]->getHeight(), _p2, _p1))
			{
				if (temppoints.size() > 0 && getClosestPoint(_p1, temppoints).x != 0 && getClosestPoint(_p1, temppoints).y != 0)
				{
					if (getClosestPoint(_p1, temppoints).x < 30 && getClosestPoint(_p1, temppoints).y < 30)
					{
						return getClosestPoint(_p1, temppoints);
					}
					return getClosestPoint(_p1, temppoints);
				}
				else
				{
					return projectLineToEdge(Point{ cameraPos.x - 10, cameraPos.y - 10 }, _p1, _p2);
				}
			}
		}
	}
	return Point{ 1000, 1000 };
}

Point CollisionDetection::projectLineToEdge(Point _c, Point _p1, Point _p2)
{
	float boundaryMinX = _c.x - screenWidth / 2;
	float boundaryMaxX = _c.x + screenWidth / 2;
	float boundaryMinY = _c.y - screenHeight / 2;
	float boundaryMaxY = _c.y + screenHeight / 2;
	Point temp1;
	Point temp2;
	temp1 = { boundaryMinX, boundaryMinY };
	temp2 = { boundaryMaxX, boundaryMinY };
	Point p1 = getLineIntersect(_p1, _p2, temp1, temp2);
	temp1 = { boundaryMaxX, boundaryMinY };
	temp2 = { boundaryMaxX, boundaryMaxY };
	Point p2 = getLineIntersect(_p1, _p2, temp1, temp2);
	temp1 = { boundaryMaxX, boundaryMaxY };
	temp2 = { boundaryMinX, boundaryMaxY };
	Point p3 = getLineIntersect(_p1, _p2, temp1, temp2);
	temp1 = { boundaryMinX, boundaryMinY };
	temp2 = { boundaryMinX, boundaryMaxY };
	Point p4 = getLineIntersect(_p1, _p2, temp1, temp2);
	vector<Point> temppoints;

	if (_p2.x >= _p1.x)
	{
		if (_p2.y >= _p1.y)
		{
			temppoints.push_back(p2);
			temppoints.push_back(p3);
			return getClosestPoint(_p1, temppoints);
		}
		if (_p2.y < _p1.y)
		{
			temppoints.push_back(p1);
			temppoints.push_back(p2);
			return getClosestPoint(_p1, temppoints);
		}
	}
	if (_p2.x < _p1.x)
	{
		if (_p2.y >= _p1.y)
		{
			temppoints.push_back(p3);
			temppoints.push_back(p4);
			return getClosestPoint(_p1, temppoints);
		}
		if (_p2.y < _p1.y)
		{
			temppoints.push_back(p4);
			temppoints.push_back(p1);
			return getClosestPoint(_p1, temppoints);
		}
	}
}

bool CollisionDetection::checkPointRectIntersect(Point _p1, Point _r, float _width, float _height)
{
	if (_p1.x >= _r.x&&_p1.x <= _r.x + _width&&_p1.y >= _r.y&&_p1.y < _r.y + _height)
	{
		return true;
	}
	else { return false; }
}
Point CollisionDetection::convertPointFromPointer(Point* _p)
{
	return Point{ _p->x, _p->y };
}
void CollisionDetection::correctPositionBounce(Rect* _player, Rect* _platform, float _bounceAmount, float _friction)
{

	//left = 1, bottom = 2, right = 3, top = 4
	if (!_player->getFixed() && CheckRectangleIntersect(_player, _platform))
	{
		switch (getSide(_player, _platform))
		{
		case 1:
			if (_player->getyVel() < 0) {
				_player->setyVel(_player->getyVel()*_friction);
			}
			if (_player->getyVel() > 0) {
				_player->setyVel(_player->getyVel()*_friction);
			}
			if (_player->getxVel() > 0) {
				_player->setxVel(_player->getxVel()*_bounceAmount);
			}
			_player->setX(_platform->getX() - _player->getWidth());
			break;
		case 3:
			if (_player->getyVel() < 0) {
				_player->setyVel(_player->getyVel()*_friction);
			}
			if (_player->getyVel() > 0) {
				_player->setyVel(_player->getyVel()*_friction);
			}
			if (_player->getxVel() < 0) {
				_player->setxVel(_player->getxVel()*-_bounceAmount);
			}
			_player->setX(_platform->getX() + _platform->getWidth());
			break;
		case 2:
			if (_player->getxVel() < 0) {
				_player->setxVel(_player->getxVel()*_friction);
			}
			if (_player->getxVel() > 0) {
				_player->setxVel(_player->getxVel()*_friction);
			}
			if (_player->getyVel() < 0) {
				_player->setyVel(_player->getyVel()*-_bounceAmount);
			}
			_player->setY(_platform->getY() + _platform->getHeight());
			break;
		case 4:
			if (_player->getxVel() < 0) {
				_player->setxVel(_player->getxVel()*_friction);
			}
			if (_player->getxVel() > 0) {
				_player->setxVel(_player->getxVel()*_friction);
			}
			if (_player->getyVel() > 0) {
				_player->setyVel(_player->getyVel()*-_bounceAmount);
			}
			_player->setY(_platform->getY() - _player->getHeight());
			break;
		}
	}
}