#include "menu.h"
#include <stdio.h>
#include "Level1.h"

void Menu::Load()
{

	Button* temp = new Level1Button(0, 0, gfx);
	buttons.push_back(temp);
	temp = new ExitButton(0, 100, gfx);
	buttons.push_back(temp);
}

void Menu::Unload() 
{
	
}

void Menu::Update()
{
	cameraPos = Point{ 0,0 };
	for (int i = 0; i < buttons.size(); i++)
	{
		if (!lastMouseLeft && mouseLeft && CollisionDetection::checkPointRectIntersect(mousePos, buttons[i]->getPosition(), 100, 50))
		{
			buttons[i]->action();
		}
	}
}
void Menu::Render()
{
	gfx->ClearScreen(0, 0, 0.02f);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw();
	}
}