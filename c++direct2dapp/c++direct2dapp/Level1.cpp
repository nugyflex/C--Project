#include "Level1.h"
#include <stdio.h>

void Level1::Load()
{

	sprites = new SpriteSheet(L"walkingleftwithbags.png", 32, 54, 0, 4, gfx);
	sprites1 = new SpriteSheet(L"sandfloor1.png", 1632, 8, 0, 0, gfx);
	soundLatch = 0;
	testvar = 0;
	fc = 0;
	

}

void Level1::Unload() {
	delete sprites;

}
;

void Level1::Update()
{
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

}
void Level1::Render()
{
	Point temppoint1 = { 1,1 };
	Point temppoint2 = { 10,10 };
	Point temppoint3 = { 1,10 };
	Point temppoint4 = { 10,1 };
		//gfx->ClearScreen(0.0f, 0.0f, 0.0f);
		sprites->autoSwitchFrame(7);
		sprites->Draw(-1, 60, 60);
		for (int i = 0; i < Rects.size(); i++)
		{
			Rects[i]->draw();
		}
		sprites1->Draw(-1, 50, 296);
}