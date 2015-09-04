#pragma once

#include "Ball.h"
#include "SpriteSheet.h"
#include "rectangle.h"
#include <vector>

using namespace std;

class GameLevel
{
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render(vector<Ball> &_Balls) = 0;
	virtual void Update(vector<Ball> &_Balls) = 0;
};