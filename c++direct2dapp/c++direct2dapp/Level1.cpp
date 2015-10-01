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

void Level1::Update(vector<Rect*> &_Rects)
{
	//VARIABLE JUMP
	if (GameController::keyW == true)
	{
		if (_Rects[0]->getyVel() >= 0)
		{
			for (int j = 0; j < _Rects.size(); j++)
			{
				if (_Rects[j]->getFixed() && CollisionDetection::getSide(_Rects[0], _Rects[j]) == 4)
				{
					_Rects[0]->setyVel(-8);
				}
			}
		}
	}
	else
	{
		if (_Rects[0]->getyVel() < -3)
		{
			_Rects[0]->setyVel(-3);
		}
	}
	if (GameController::keyA == true)
	{

		
		_Rects[0]->setxVel(-3);
		
		
	}
	else
	{
		soundLatch = 0;
	}
	if (GameController::keyS == true)
	{
		//_Rects[0]->setyVel(6);
	}
	if (GameController::keyD == true)
	{
		_Rects[0]->setxVel(3);

	}
	if (GameController::keyA == false && GameController::keyD == false)
	{
		_Rects[0]->setxVel(0);
	}
	for (int i = 0; i < _Rects.size(); i++)
	{
		//Gravity
		if (_Rects[i]->getGravity() == true)
		{
			_Rects[i]->setyVel(_Rects[i]->getyVel() + 0.51f);
		}
		//adding xvel x to x and yvel to y
		_Rects[i]->calcNewPos();
		if (_Rects[i]->getType() == spy)
		{
			_Rects[i]->calcNewPos(_Rects[0]->getPosition());
		}

		if (!_Rects[i]->getFixed() && _Rects[i]->getType() != fireball)
		{
			for (int j = 0; j < _Rects.size(); j++)
			{
				if (_Rects[j]->getFixed())
				{
					CollisionDetection::correctPosition(_Rects[i], _Rects[j]);
				}
			}
		}

	}

	for (int i = 0; i < _Rects.size(); i++)
	{
		//deleting fireballs
		if (_Rects[i]->getType() == fireball)
		{

			for (int j = 0; j < _Rects.size(); j++)
			{
				if (_Rects[j]->getType() == platform)
				{
					if (CollisionDetection::CheckRectangleIntersect(_Rects[i], _Rects[j]))
					{
						_Rects.erase(_Rects.begin() + i);
						i--;
						break;
					}
				}
			}

		}
	}

}
void Level1::Render(vector<Rect*> _Rects)
{
	Point temppoint1 = { 1,1 };
	Point temppoint2 = { 10,10 };
	Point temppoint3 = { 1,10 };
	Point temppoint4 = { 10,1 };
		//gfx->ClearScreen(0.0f, 0.0f, 0.0f);
		sprites->autoSwitchFrame(7);
		sprites->Draw(-1, 60, 60);
		for (int i = 0; i < _Rects.size(); i++)
		{
			_Rects[i]->draw();
		}
		sprites1->Draw(-1, 50, 296);
}