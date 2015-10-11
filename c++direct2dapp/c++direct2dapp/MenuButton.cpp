#include "MenuButton.h"
#include "GameController.h"
#include "menu.h"

MenuButton::MenuButton()
{

}
MenuButton::~MenuButton() {}

MenuButton::MenuButton(int _x, int _y, Graphics * _gfx):
Button(_x, _y, _gfx)
{

}
void MenuButton::action()
{
	GameController::SwitchLevel(new Menu());
	//
}
void MenuButton::draw()
{
	gfx->FillRect(position, 100, 50, 1.0f, 1.0f, 1.0f, 1.0f);
} 