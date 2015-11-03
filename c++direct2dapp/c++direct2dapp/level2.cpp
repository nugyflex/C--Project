#include "level2.h"
#include <stdio.h>
#include <math.h>

void level2::loadObjects() //loads the level, called when the level is instantiated
{
	backGround = new SpriteSheet(L"sanddunes.png", screenWidth, screenHeight, 0, 0, gfx);
	boundaryIn.x = -10000;
	boundaryIn.y = -10000;
	boundaryOut.x = 10000;
	boundaryOut.y = 1300;
	exitPoints.push_back(new exitPoint(Point{ 360, 1250 }, 80, 200, 60, 0, 3));
	Rects.push_back(new Player(Point{ 60, 60 }, 12, 54, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 0, 0 }, 800, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 0, 0 }, 50, 1400, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 750, 0 }, 50, 1400, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 0, 600 }, 360, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 440, 600 }, 360, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 100, 1000 }, 600, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 0, 1250 }, 360, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 440, 1250 }, 360, 50, 0, 0, gfx));
	Rects.push_back(new Spy(Point{ 700, 750 }, 10, 10, 0, 0, Point{ 100, 750 }, Point{ 700, 750 }, gfx));
	Rects.push_back(new Spy(Point{ 100, 800 }, 10, 10, 0, 0, Point{ 100, 800 }, Point{ 700, 800 }, gfx));
	Rects.push_back(new Hunter(Point{ 700, 1200 }, 10, 10, 0, 0, Point{ 100, 1200 }, Point{ 700, 1200 }, gfx));
	Rects.push_back(new Spy(Point{ 700, 1100 }, 10, 10, 0, 0, Point{ 100, 1100 }, Point{ 700, 1100 }, gfx));
	Rects.push_back(new Spy(Point{ 100, 1150 }, 10, 10, 0, 0, Point{ 100, 1150 }, Point{ 700, 1150 }, gfx));
	Gun* newgun = new Gun(300, 300, gfx);
	weapons.push_back(newgun);
	weapons[0]->load();
	weapons[0]->setParent(true);
	((Player*)Rects[0])->addWeapon(weapons[0]);
}