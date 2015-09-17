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

void Level1::Update(vector<Rect*> _Rects)
{
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
		_Rects[i]->setyVel(_Rects[i]->getyVel() + 0.51f);
		//adding xvel x to x and yvel to y
		_Rects[i]->calcNewPos();
		if (!_Rects[i]->getFixed())
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
	char s[200];
	sprintf_s(s, " Number of elements at start: %d.", _Rects.size());
	OutputDebugString(s);
	for (int i = 0; i < _Rects.size(); i++)
	{
		//deleting fireballs
		if (_Rects[i]->getType() == fireball)
		{
			sprintf_s(s, " About to delete: %d.", i);
			OutputDebugString(s);

			_Rects.erase(_Rects.begin() + i);
			i--;
		}
	}
	sprintf_s(s, " Number of elements at end: %d.", _Rects.size());
	OutputDebugString(s);


}
void Level1::Render(vector<Rect*> _Rects)
{

	if (CollisionDetection::CheckRectangleIntersect(1, 1, 10, 10, 5, 5, 15, 15))
	{
		//gfx->ClearScreen(0.0f, 0.0f, 0.0f);
		sprites->autoSwitchFrame(7);
		sprites->Draw(-1, 60, 60);

		for (int i = 0; i < _Rects.size(); i++)
		{
			_Rects[i]->draw();
		}
		sprites1->Draw(-1, 50, 296);

	}
}