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

void GameController::Render(vector<Rect*> _Rects)
{
	if (Loading) return;
	currentlevel->Render(_Rects);
}

void GameController::Update(vector<Rect*> &_Rects)
{
	if (Loading) return;
	currentlevel->Update(_Rects);
}
void GameController::setMouseX(int _x)
{
	mouse.x = _x;
}
void GameController::setMouseY(int _y)
{
	mouse.y = _y;
}
Point GameController::getMousePos()
{
	return mouse;
}