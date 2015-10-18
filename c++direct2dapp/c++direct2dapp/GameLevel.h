#pragma once


#include "Player.h"
#include "Platform.h"
#include "fireball.h"
#include "spy.h"
#include "gun.h"
#include "Camera.h"
#include "MenuButton.h"
#include "Level1Button.h"
#include "ExitButton.h"
#include <vector>

using namespace std;

class gameLevel
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