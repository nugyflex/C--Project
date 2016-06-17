#pragma once
#include "rectangle.h"
#include "Math.h"
#include <vector>
#include "Particle.h"
class CollisionDetection
{
	CollisionDetection() {}
public:
	static bool CheckRectangleIntersect(Rect *_ob1, Point _p1, int _width, int _height);
	static bool CheckRectangleIntersect(Rect *_ob1, Rect *_ob2);
	static float finddistance(float x1, float y1, float x2, float y2);
	static bool test1(Rect *player, Rect *platform);
	static bool test2(Rect *player, Rect *platform);
	static bool test3(Rect *player, Rect *platform);
	static bool test4(Rect *player, Rect *platform);
	static bool test5(Rect *player, Rect *platform);
	static bool test6(Rect *player, Rect *platform);
	static bool test7(Rect *player, Rect *platform);
	static bool test8(Rect *player, Rect *platform);
	static int getSide(Rect *player, Rect *platform);
	static void correctPosition(Rect* player, Rect* platform);
	static Point getLineIntersect(Point _p1, Point _p2, Point _p3, Point _p4);
	static bool checkLineIntersect(Point _p1, Point _p2, Point _p3, Point _p4);
	static bool isBetween(float _1, float _2, float _3);
	static bool checkRectLineIntersect(Point _rp, float _width, float _height, Point _p1, Point _p2);
	static Point getClosestRectLineIntersect(Point _rp, float _width, float _height, Point _p1, Point _p2);
	static Point getClosestPoint(Point _p, vector<Point> _Points);
	static Point getClosestTarget(Point _p1, Point _p2);
	static Point projectLineToEdge(Point _c, Point _p1, Point _p2);
	static bool checkPointRectIntersect(Point _p1, Point _r, float width, float height);
	static void correctPositionParticle(Particle* _particle, Rect* _platform);
	static void correctPositionBounce(Rect* _player, Rect* _platform, float _bounceAmount, float _friction);
	static Point convertPointFromPointer(Point* _p);
};