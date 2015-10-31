#include "MenuButton.h"
#include "gameController.h"
#include "menu.h"

MenuButton::MenuButton()
{
}
MenuButton::~MenuButton() {}

MenuButton::MenuButton(int _x, int _y, Graphics * _gfx) :
	Button(_x, _y, _gfx)
{
}
void MenuButton::action()
{
	gameController::SwitchLevel(new Menu());
}
void MenuButton::draw()
{
	gfx->FillRect(Point{ position.x + cameraPos.x, position.y + cameraPos.y }, 100, 50, 1.0f, 1.0f, 1.0f, 1.0f);
}