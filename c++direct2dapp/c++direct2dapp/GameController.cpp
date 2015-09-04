#include "GameController.h"
#include <vector>


GameLevel* GameController::currentlevel;
bool GameController::Loading;
bool GameController::keyW;
bool GameController::keyA;
bool GameController::keyS;
bool GameController::keyD;


void GameController::Init()
{
	Loading = true;
	currentlevel = 0;
}

void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true;
	currentlevel = lev;
	currentlevel->Load();
	Loading = false;
}

void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentlevel->Unload();
	lev->Load();
	delete currentlevel;
	currentlevel = lev;
	Loading = false;
}

void GameController::Render(vector<Ball> &_Balls)
{
	if (Loading) return;
	currentlevel->Render(_Balls);
}

void GameController::Update(vector<Ball> &_Balls)
{
	if (Loading) return;
	currentlevel->Update(_Balls);
}
