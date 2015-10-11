#include "Level1Button.h"
#include "GameController.h"
#include "Level1.h"

Level1Button::Level1Button()
{

}
Level1Button::~Level1Button() {}

Level1Button::Level1Button(int _x, int _y, Graphics * _gfx) :
	Button(_x, _y, _gfx)
{

}
void Level1Button::action()
{
	GameController::SwitchLevel(new Level1());
}
void Level1Button::draw()
{
	gfx->FillRect(position, 100, 50, 1.0f, 1.0f, 1.0f, 1.0f);
}