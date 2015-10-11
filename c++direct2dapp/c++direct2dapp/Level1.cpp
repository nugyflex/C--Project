#include "Level1.h"
#include <stdio.h>

void Level1::Load()
{


	soundLatch = 0;
	testvar = 0;
	fc = 0;
	Button* temp = new MenuButton(600, 0, gfx);
	buttons.push_back(temp);
	temp = new ExitButton(600, 100, gfx);
	buttons.push_back(temp);


	camera = new Camera(Point{ 0,0 });
	backGround  = new SpriteSheet(L"sanddunes2.png", 1280, 720, 0, 0, gfx);

	Rect* tempobject = new Player(Point{ 640,9 }, 32, 54, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 50, 298 }, 1200, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 50, 500 }, 1600, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 500, 450 }, 50, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new FireBall(Point{ 200, 200 }, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Spy(Point{ 200, 200 }, 10, 10, 0, 0, gfx);
	Rects.push_back(tempobject);
	Rects[0]->load();
	Rects[4]->load();
	Rects[5]->load();
	Gun* newgun = new Gun(300, 300, gfx);
	weapons.push_back(newgun);
	weapons[0]->load();
	weapons[0]->setParent(true);
	((Player*)Rects[0])->addWeapon(weapons[0]);
	paused = false;

}

void Level1::Unload() {
	delete backGround;
	delete camera;
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	for (auto it = Rects.begin(); it != Rects.end(); ++it) {
		delete *it;
	}
	Rects.clear();
}

void Level1::Update()
{
	//makes the mouse movie with the camera
	GameController::mouse.x += camera->getxVel();
	GameController::mouse.y += camera->getyVel();
	camera->calcNewPos(Rects[0]->getPosition());
	cameraPos = camera->getPosition();
	
	//VARIABLE JUMP
	if (GameController::keyW == true)
	{
		if (Rects[0]->getyVel() >= 0)
		{
			for (int j = 0; j < Rects.size(); j++)
			{
				if (Rects[j]->getFixed() && CollisionDetection::getSide(Rects[0], Rects[j]) == 4)
				{
					Rects[0]->setyVel(-8);
				}
			}
		}
	}
	else
	{
		if (Rects[0]->getyVel() < -3)
		{
			Rects[0]->setyVel(-3);
		}
	}
	if (GameController::keyA == true)
	{

		
		Rects[0]->setxVel(-3);
		
		
	}
	else
	{
		soundLatch = 0;
	}
	if (GameController::keyS == true)
	{
		//Rects[0]->setyVel(6);
	}
	if (GameController::keyD == true)
	{
		Rects[0]->setxVel(3);

	}
	if (GameController::keyA == false && GameController::keyD == false)
	{
		Rects[0]->setxVel(0);
	}
	for (int i = 0; i < Rects.size(); i++)
	{
		//Gravity
		if (Rects[i]->getGravity() == true)
		{
			Rects[i]->setyVel(Rects[i]->getyVel() + 0.51f);
		}
		//adding xvel x to x and yvel to y
		Rects[i]->calcNewPos();
		if (Rects[i]->getType() == spy)
		{
			Rects[i]->calcNewPos(Rects[0]->getPosition());
		}

		if (!Rects[i]->getFixed() && Rects[i]->getType() != fireball)
		{
			for (int j = 0; j < Rects.size(); j++)
			{
				if (Rects[j]->getFixed())
				{
					CollisionDetection::correctPosition(Rects[i], Rects[j]);
				}
			}
		}

	}

	for (int i = 0; i < Rects.size(); i++)
	{
		//deleting fireballs
		if (Rects[i]->getType() == fireball)
		{

			for (int j = 0; j < Rects.size(); j++)
			{
				if (Rects[j]->getType() == platform)
				{
					if (CollisionDetection::CheckRectangleIntersect(Rects[i], Rects[j]))
					{
						Rects.erase(Rects.begin() + i);
						i--;
						break;
					}
				}
			}

		}
	}
	if (paused)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			if (mouseLeft && CollisionDetection::checkPointRectIntersect(mousePos, buttons[i]->getPosition(), 100, 50))
			{
				buttons[i]->action();
			}
		}
	}

}
void Level1::Render()
{
	backGround->Draw(0, camera->getPosition().x - 640, camera->getPosition().y - 360);
	Point temppoint1 = { 1,1 };
	Point temppoint2 = { 10,10 };
	Point temppoint3 = { 1,10 };
	Point temppoint4 = { 10,1 };
		//gfx->ClearScreen(0.0f, 0.0f, 0.0f);

		for (int i = 0; i < Rects.size(); i++)
		{
			Rects[i]->draw();
		}
		if (paused)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				buttons[i]->draw();
			}
		}
}