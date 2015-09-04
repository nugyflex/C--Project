#include "Level1.h"


void Level1::Load()
{

	sprites = new SpriteSheet(L"test.png", gfx);

}

void Level1::Unload() {
	delete sprites;

}
;

void Level1::Update(vector<Ball> &_Balls)
{
	if (GameController::keyW == true)
	{
		_Balls[0].setyVel(-6);
	}
	if (GameController::keyA == true)
	{
		_Balls[0].setxVel(-6);
	}
	if (GameController::keyS == true)
	{
		_Balls[0].setyVel(6);
	}
	if (GameController::keyD == true)
	{
		_Balls[0].setxVel(6);
	}
	if (GameController::keyA == false && GameController::keyD == false)
	{
		_Balls[0].setxVel(0);
	}
	/*
	for (int i = 0; i < _Balls.size; i++)
	{
		//Gravity
		_Balls[i].setyVel(_Balls[i].getyVel() + 0.5f);
		//adding xvel x to x and yvel to y
		_Balls[i].calcNewPos();
		//making sure that the balls dont go through the floor
		if (_Balls[i].getY() > 600 - _Balls[i].getRadius())

		{
			_Balls[i].setY(600 - _Balls[i].getRadius());
			_Balls[i].setyVel(_Balls[i].getyVel()*-0.8);
		}
	}*/
}
void Level1::Render(vector<Ball> &_Balls)
{
//sprites->Draw();
	if (CollisionDetection::CheckRectangleIntersect(1, 1, 10, 10, 5, 5, 15, 15))
	{
		gfx->ClearScreen(0.0f, 0.0f, 0.0f);
		_Balls[0].draw();
		_Balls[1].draw();
	}
}