#include "gameController.h"
#include <vector>

gameLevel* gameController::currentlevel; //the gameController class, this runs the game
bool gameController::Loading;
bool gameController::space;
bool gameController::keyW;
bool gameController::keyA;
bool gameController::keyS;
bool gameController::keyD;
float gameController::zoomLevel;
int gameController::fps;
Point gameController::mouse;
bool gameController::mouseMoved;
bool gameController::mouseLeft;

void gameController::Init()
{
	Loading = true;
	currentlevel = 0;
}

void gameController::LoadInitialLevel(gameLevel* lev)
{
	Loading = true;
	currentlevel = lev;
	currentlevel->Load();
	Loading = false;
}

void gameController::SwitchLevel(gameLevel* lev)
{
	paused = false;
	Loading = true;
	currentlevel->Unload();
	lev->Load();
	delete currentlevel;
	currentlevel = lev;
	Loading = false;
}

void gameController::Render()
{
	if (Loading) return;
	currentlevel->Render();
}

void gameController::Update()
{
	if (Loading) return;
	currentlevel->Update();
}
void gameController::setMouseX(float _x)
{
	mouse.x = _x;
}
void gameController::setMouseY(float _y)
{
	mouse.y = _y;
}
Point gameController::getMousePos()
{
	return mouse;
}