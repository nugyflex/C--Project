#include "Level1.h"
#include <stdio.h>
#include <math.h>

void Level1::loadObjects() //loads the level, called when the level is instantiated
{
	backGround = new SpriteSheet(L"sanddunes.png", screenWidth, screenHeight, 0, 0, gfx);
	boundaryIn.x = 0;
	boundaryIn.y = -2000;
	boundaryOut.x = 8000;
	boundaryOut.y = 650;
	Rects.push_back(new Player(Point{ 200, 240 }, 12, 54, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 50, 300 }, 1200, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 1300, 300 }, 75, 25, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -100, 500 }, 1600, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 550, 200 }, 50, 100, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 500, 250 }, 50, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 600, 250 }, 50, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 500, 450 }, 50, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 1300, 450 }, 50, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 1350, 400 }, 50, 100, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 1400, 350 }, 50, 150, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 1450, 300 }, 50, 200, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 1500, 0 }, 1000, 550, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 0, 0 }, 50, 400, 0, 0, gfx));
	//Rects.push_back(new FireBall(Point{ 200, 200 }, 0, 0, gfx));
	exitPoints.push_back(new exitPoint(Point{ -20, 400 }, 70, 100, 80, -1));
	Rects.push_back(new Spy(Point{ 750, 220 }, 10, 10, 0, 0, Point{ 710, 220 }, Point{ 1000, 220 }, gfx));
	Rects.push_back(new Spy(Point{ 1050, 220 }, 10, 10, 0, 0, Point{ 1050, 220 }, Point{ 1400, 220 }, gfx));
	Rects.push_back(new Spy(Point{ 220, 400 }, 10, 10, 0, 0, Point{ 100, 400 }, Point{ 800, 400 }, gfx));
	Gun* newgun = new Gun(300, 300, gfx);
	weapons.push_back(newgun);
	weapons[0]->load();
	weapons[0]->setParent(true);
	((Player*)Rects[0])->addWeapon(weapons[0]);
}