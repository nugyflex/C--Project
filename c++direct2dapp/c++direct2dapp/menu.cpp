#include "menu.h"
#include <stdio.h>
#include "Level1.h"

void Menu::Load()
{
	Button* temp = new Level1Button(0, 0, gfx);
	Buttons.push_back(temp);
	temp = new ExitButton(0, 100, gfx);
	Buttons.push_back(temp);
	Buttons.push_back(new LevelEditorButton(0, 200, gfx));
}

void Menu::Unload()
{
	for (int i = 0; i < Buttons.size(); i++)
	{
		delete Buttons[i];
	}
	Buttons.clear();
}

void Menu::Update()
{
	cameraPos = Point{ 0,0 };
}
void Menu::Render()
{
	gfx->ClearScreen(0, 0, 0.02f);
	for (int i = 0; i < Buttons.size(); i++)
	{
		Buttons[i]->draw();
	}
}
void Menu::HandleInput()
{
	for (int i = 0; i < Buttons.size(); i++)
	{
		if (!lastMouseLeft && mouseLeft)
		{
			Point test = Buttons[i]->getPosition();
			if (CollisionDetection::checkPointRectIntersect(mousePos, Buttons[i]->getPosition(), 100, 50))
			{
				Buttons[i]->action();
				break;
			}
		}
	}
}