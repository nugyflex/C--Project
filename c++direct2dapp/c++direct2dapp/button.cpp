#include "button.h"
Button::Button()
{
}
Button::Button(int _x, int _y, Graphics * _gfx)
{
	gfx = _gfx;
	position.x = _x;
	position.y = _y;
}
Button::Button(int _x, int _y, int _width, int _height, editorMode _mode, Graphics * _gfx)
{
	position.x = _x;
	position.y = _y;
	type = changemode;
	modeToSwitchTo = _mode;
	width = _width;
	height = _height;
	gfx = _gfx;
	alignWithCamera = false;
}
Button::Button(int _x, int _y, int _width, int _height, editorMode _mode, bool _alignWithCamera, screenSide _ScreenSide, Graphics * _gfx)
{
	alignWithCamera = _alignWithCamera;
	if (_alignWithCamera)
	{
		cameraOffSet.x = _x;
		cameraOffSet.y = _y;
		ScreenSide = _ScreenSide;
	}
		position.x = _x;
		position.y = _y;
	type = changemode;
	modeToSwitchTo = _mode;
	width = _width;
	height = _height;
	gfx = _gfx;
}
Button::~Button() {}

void Button::action() {}

void Button::draw()
{
	if (alignWithCamera)
	{
		switch (ScreenSide)
		{
		case topLeft:
			position = Point{ (cameraPos.x - screenWidth / 2) + cameraOffSet.x, (cameraPos.y - screenHeight / 2) + cameraOffSet.y };
			break;
		case bottomLeft:
			position = Point{ (cameraPos.x - screenWidth / 2) + cameraOffSet.x, (cameraPos.y + screenHeight / 2) + cameraOffSet.y };
			break;
		case topRight:
			position = Point{ (cameraPos.x + screenWidth / 2) + cameraOffSet.x, (cameraPos.y - screenHeight / 2) + cameraOffSet.y };
			break;
		case bottomRight:
			position = Point{ (cameraPos.x + screenWidth / 2) + cameraOffSet.x, (cameraPos.y + screenHeight / 2) + cameraOffSet.y };
			break;
		}
		
	}
	gfx->FillRect(position, width, height, 0.5, 0.5, 0.5, 1);
	gfx->FillRect(Point{ position.x + 3, position.y + 3 }, width - 6, height - 6, 0.9, 0.9, 0.9, 1);
	if (CollisionDetection::checkPointRectIntersect(mousePos, position, width, height))
	{
		gfx->FillRect(Point{ position.x + 3, position.y + 3 }, width - 6, height - 6, 0.3, 0.3, 0.3, 1);
		if (mouseLeft)
		{
			gfx->FillRect(Point{ position.x + 3, position.y + 3 }, width - 6, height - 6, 0.15, 0.15, 0.15, 1);
		}
	}
}

Point Button::getPosition()
{
	return position;
}
buttonType Button::getType()
{
	return type;
}
int Button::getWidth()
{
	return width;
}
int Button::getHeight()
{
	return height;
}
editorMode Button::getEditorMode()
{
	return modeToSwitchTo;
}
std::vector<Button*> Buttons;