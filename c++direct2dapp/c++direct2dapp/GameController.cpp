#include "GameController.h"

GameLevel* GameController::currentlevel;
bool GameController::Loading;

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

void GameController::Render()
{
	if (Loading) return;
	currentlevel->Render();
}

void GameController::Update()
{
	if (Loading) return;
	currentlevel->Update();
}