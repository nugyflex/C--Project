#pragma once
#include "rectangle.h"
#include "Math.h"

class CollisionDetection
{
	CollisionDetection() {}
public:
	static bool CheckRectangleIntersect(float x1, float x2, float y1, float y2, float x3, float x4, float y3, float y4);
	static int finddistance(float x1, float y1, float x2, float y2);
	static bool test1(Rect *player, Rect *platform);
	static bool test2(Rect *player, Rect *platform);
	static bool test3(Rect *player, Rect *platform);
	static bool test4(Rect *player, Rect *platform);
	static bool test5(Rect *player, Rect *platform);
	static bool test6(Rect *player, Rect *platform);
	static bool test7(Rect *player, Rect *platform);
	static bool test8(Rect *player, Rect *platform);
	static int getSide(Rect &player, Rect &platform);
	static void correctPosition(Rect &player, Rect &platform);
};