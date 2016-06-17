#include "editorLevel.h"

void editorLevel::Load()
{
	LevelEditor = new levelEditor(gfx);
	Buttons.push_back(new MenuButton(0, 0, gfx));
	Buttons.push_back(new ExitButton(0, 100, gfx));
}
void editorLevel::Render()
{
	gfx->ClearScreen(0.25, 0.55, 1);

	LevelEditor->draw();
	for (int i = 0; i < Buttons.size(); i++)
	{
		if (Buttons[i]->getType() == nothing)
		{
			if (paused)
			{
				Buttons[i]->draw();
			}
		}
		else
		{
			Buttons[i]->draw();
		}
	}
}
void editorLevel::Unload()
{

	Buttons.clear();
	for (int i = 0; i < Rects.size(); i++)
	{
		delete Rects[i];
	}
	Rects.clear();
	delete LevelEditor;
	for (int i = 0; i < Buttons.size(); i++)
	{
		delete Buttons[i];
	}
}
void editorLevel::Update()
{

	if (!paused)
	{
		LevelEditor->update();
	}
}
void editorLevel::HandleInput()
{
	if (paused)
	{
		for (int i = 0; i < Buttons.size(); i++)
		{
			if (!lastMouseLeft && mouseLeft && CollisionDetection::checkPointRectIntersect(mousePos, Point{ Buttons[i]->getPosition().x + cameraPos.x, Buttons[i]->getPosition().y + cameraPos.y }, 100, 50))
			{
				Buttons[i]->action();
			}
		}
	}
}