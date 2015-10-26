#include "ExitButton.h"
#include "gameController.h"
#include <stdlib.h>

ExitButton::ExitButton()
{

}
ExitButton::~ExitButton() {}

ExitButton::ExitButton(int _x, int _y, Graphics * _gfx) :
	Button(_x, _y, _gfx)
{

}
void ExitButton::action()
{
	exit(0);
}
void ExitButton::draw()
{
	gfx->FillRect(Point{ position.x + cameraPos.x, position.y + cameraPos.y }, 100, 50, 1.0f, 0.3f, 0.3f, 1.0f);
}