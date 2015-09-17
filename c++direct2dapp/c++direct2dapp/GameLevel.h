#pragma once


#include "Player.h"
#include "Platform.h"
#include "fireball.h"
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
	virtual void Render(vector<Rect*> _Rects) = 0;
	virtual void Update(vector<Rect*> _Rects) = 0;
};