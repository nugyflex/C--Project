#pragma once

#include "GameLevel.h"
#include <vector>


using namespace std;

class GameController
{
	GameController() {}
public:
	static GameLevel* currentlevel;

public:
	static Point mouse;
	static bool Loading;
	static bool keyW;
	static bool keyA;
	static bool keyS;
	static bool keyD;
	static int fps;
	static float zoomLevel;
	static bool mouseMoved;
	static bool mouseLeft;
		 
	static void Init();

	static void LoadInitialLevel(GameLevel* lev);
	static void  SwitchLevel(GameLevel* lev);

	static void Render();
	static void Update();
	static void setMouseX(float _x);
	static void setMouseY(float _y);
	static Point  getMousePos();
};