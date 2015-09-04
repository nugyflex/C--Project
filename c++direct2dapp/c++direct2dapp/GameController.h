#pragma once

#include "GameLevel.h"
#include "Ball.h"
#include <vector>
#include "rectangle.h"


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
		 
	static void Init();

	static void LoadInitialLevel(GameLevel* lev);
	static void  SwitchLevel(GameLevel* lev);

	static void Render(vector<Ball> &_Balls);
	static void Update(vector<Ball> &_Balls);


};