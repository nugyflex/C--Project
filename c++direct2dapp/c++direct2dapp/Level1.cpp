#include "Level1.h"


void Level1::Load()
{

	sprites = new SpriteSheet(L"gradient_sprite.png", 100, 100, 0, gfx);

}

void Level1::Unload() {
	delete sprites;

}
;

void Level1::Update(vector<Rect> &_Rects)
{
	if (GameController::keyW == true)
	{
		if (_Rects[0].getyVel() >= 0)
		{
			for (int j = 0; j < _Rects.size(); j++)
			{
				if (_Rects[j].getFixed() && CollisionDetection::getSide(_Rects[0], _Rects[j]) == 4)
				{
					_Rects[0].setyVel(-15);
				}
			}
		}
	}
	if (GameController::keyA == true)
	{

		
		_Rects[0].setxVel(-6);
		gfx->setZoomLevel(gfx->getZoomLevel() + 0.01);
		
	}
	if (GameController::keyS == true)
	{
		_Rects[0].setyVel(6);
	}
	if (GameController::keyD == true)
	{
		_Rects[0].setxVel(6);
		gfx->setZoomLevel(gfx->getZoomLevel() - 0.01);
	}
	if (GameController::keyA == false && GameController::keyD == false)
	{
		_Rects[0].setxVel(0);
	}
	for (int i = 0; i < _Rects.size(); i++)
	{
		//Gravity
		_Rects[i].setyVel(_Rects[i].getyVel() + 0.5f);
		//adding xvel x to x and yvel to y
		_Rects[i].calcNewPos();
		if (!_Rects[i].getFixed())
		{
			for (int j = 0; j < _Rects.size(); j++)
			{
				if (_Rects[j].getFixed())
				{
					CollisionDetection::correctPosition(_Rects[i], _Rects[j]);
				}
			}
		}

	}



}
void Level1::Render(vector<Rect> &_Rects)
{

	if (CollisionDetection::CheckRectangleIntersect(1, 1, 10, 10, 5, 5, 15, 15))
	{
		gfx->ClearScreen(0.0f, 0.0f, 0.0f);
		sprites->Draw(0, 60, 60);
		for (int i = 0; i < _Rects.size(); i++)
		{
			_Rects[i].draw();
		}
	}
}