#pragma once

#include "GameLevel.h"

#include "CollisionDetection.h"
#include "GameController.h"
#include "Graphics.h"





class Level1 : public GameLevel
{
	float y;
	float yVel;

	SpriteSheet* sprites;

public:

	void Load() override;
	void Unload() override;
	void Render(vector<Ball> &_Balls);
	void Update(vector<Ball> &_Balls);
};