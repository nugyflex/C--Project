#pragma once

#include "gameLevel.h"
#include <vector>

using namespace std;

class gameController
{
	gameController() {}
public:
	static gameLevel* currentlevel;

public:
	static Point mouse;
	static bool space;
	static bool Loading;
	static bool keyW;
	static bool keyA;
	static bool keyS;
	static bool keyD;
	static bool keyQ;
	static bool keyZ;
	static bool shift;
	static bool control;
	static int fps;
	static float zoomLevel;
	static bool mouseMoved;
	static bool mouseLeft;

	static void Init();

	static void LoadInitialLevel(gameLevel* lev);
	static void  SwitchLevel(gameLevel* lev);

	static void HandleInput();
	static void Render();
	static void Update();
	static void setMouseX(float _x);
	static void setMouseY(float _y);
	static Point  getMousePos();
};