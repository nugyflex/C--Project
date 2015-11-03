#include "Level3.h"
#include <stdio.h>
#include <math.h>

void Level3::loadObjects() //loads the level, called when the level is instantiated
{
	backGround = new SpriteSheet(L"sanddunes.png", screenWidth, screenHeight, 0, 0, gfx);
	boundaryIn.x = -10000;
	boundaryIn.y = 0;
	boundaryOut.x = 1800;
	boundaryOut.y = 1300;
	exitPoints.push_back(new exitPoint(Point{ -400, 200 }, 50, 200, 60, -1, 1));
	Rects.push_back(new Player(Point{ 280, 0 }, 12, 54, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -100, 0 }, 360, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 340, 0 }, 460, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 0, 0 }, 50, 500, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 800, 0 }, 1000, 500, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 0, 450 }, 360, 50, 0, 0, gfx));
	//Rects.push_back(new Platform(Point{ 440, 450 }, 360, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ 430, 450 }, 1500, 150, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -110, 600 }, 590, 50, 0, 0, gfx));
	//steps
	Rects.push_back(new Platform(Point{ -50, 550 }, 10, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -60, 500 }, 10, 100, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -70, 450 }, 10, 150, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -110, 450 }, 50, 150, 0, 0, gfx));
	//
	Rects.push_back(new Platform(Point{ -200, 200 }, 200, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -400, 200 }, 150, 50, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -300, 100 }, 50, 100, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -300, 0 }, 150, 150, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -400, 0 }, 100, 250, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -200, 0 }, 200, 200, 0, 0, gfx));
	Rects.push_back(new Platform(Point{ -400, 450 }, 340, 50, 0, 0, gfx));


	Rects.push_back(new Spy(Point{ -240, 160 }, 10, 10, 0, 0, gfx));
	Rects.push_back(new Spy(Point{ -230, 160 }, 10, 10, 0, 0, gfx));
	Rects.push_back(new Spy(Point{ -240, 170 }, 10, 10, 0, 0, gfx));
	Rects.push_back(new Spy(Point{ -230, 170 }, 10, 10, 0, 0, gfx));
	Rects.push_back(new Hunter(Point{ -50, 560 }, 10, 10, 0, 0, Point{ -50, 560 }, Point{ 400, 560 }, gfx));
	Gun* newgun = new Gun(300, 300, gfx);
	weapons.push_back(newgun);
	weapons[0]->load();
	weapons[0]->setParent(true);
	((Player*)Rects[0])->addWeapon(weapons[0]);
}