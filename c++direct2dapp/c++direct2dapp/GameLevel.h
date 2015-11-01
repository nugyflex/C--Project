#pragma once

#include "Platform.h"
#include "fireball.h"
#include "spy.h"
#include "hunter.h"
#include "gun.h"
#include "Camera.h"
#include "MenuButton.h"
#include "Level1Button.h"
#include "ExitButton.h"
#include "exitPoint.h"
#include <vector>

using namespace std;

class gameLevel //the gameLevel class, inherited by Level1 and Menu
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
	virtual void Render() = 0;
	virtual void Update() = 0;
};