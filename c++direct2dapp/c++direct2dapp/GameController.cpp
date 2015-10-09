#include "GameController.h"
#include <vector>


GameLevel* GameController::currentlevel;
bool GameController::Loading;
bool GameController::keyW;
bool GameController::keyA;
bool GameController::keyS;
bool GameController::keyD;
float GameController::zoomLevel;
int GameController::fps;
Point GameController::mouse;
bool GameController::mouseMoved;
bool GameController::mouseLeft;


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
void GameController::setMouseX(float _x)
{
	mouse.x = _x;
}
void GameController::setMouseY(float _y)
{
	mouse.y = _y;
}
Point GameController::getMousePos()
{
	return mouse;
}