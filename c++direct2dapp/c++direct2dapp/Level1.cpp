#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

void Level1::Load()
{
	y = yVel = 0.0f;
}

void Level1::Unload() {}

void Level1::Update()
{
	yVel += 0.5f;


	y += yVel;

	if (y > 530)

	{
		y = 530;
		yVel = yVel*-0.8;
	}
}void Level1::Render()
{

	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	gfx->DrawCircle(200.0f, y, 70.0f, 1.0f, 1.0f, 1.0f, 1.0f);

}