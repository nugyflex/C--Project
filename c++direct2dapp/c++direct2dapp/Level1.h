#pragma once

#include "GameLevel.h"
#include "CollisionDetection.h"
#include "GameController.h"
#include "Graphics.h"





class Level1 : public GameLevel
{
	float y;
	float yVel;
	int soundLatch;
	int testvar;
	int fc;

	SpriteSheet* sprites;

public:

	void Load() override;
	void Unload() override;
	void Render(vector<Rect> &_Rects);
	void Update(vector<Rect> &_Rects);
};