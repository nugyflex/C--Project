#include "LevelEditorButton.h"
#include "gameController.h"
#include "editorLevel.h"

LevelEditorButton::LevelEditorButton()
{
}
LevelEditorButton::~LevelEditorButton() {}

LevelEditorButton::LevelEditorButton(int _x, int _y, Graphics * _gfx) :
	Button(_x, _y, _gfx)
{
}
void LevelEditorButton::action()
{
	gameController::SwitchLevel(new editorLevel());
}
void LevelEditorButton::draw()
{
	gfx->FillRect(Point{ position.x + cameraPos.x, position.y + cameraPos.y }, 100, 50, 0.4f, 1.0f, 0.6f, 1.0f);
}