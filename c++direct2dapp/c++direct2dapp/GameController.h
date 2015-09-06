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
	static bool Loading;
	static bool keyW;
	static bool keyA;
	static bool keyS;
	static bool keyD;
	static float zoomLevel;
		 
	static void Init();

	static void LoadInitialLevel(GameLevel* lev);
	static void  SwitchLevel(GameLevel* lev);

	static void Render(vector<Rect> &_Rects);
	static void Update(vector<Rect> &_Rects);


};