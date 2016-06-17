#pragma once
#include "Graphics.h"
#include "CollisionDetection.h"
#include <vector>
enum buttonType {changemode, nothing};
enum editorMode { placePlatform, none, toggleGrid, toggleSnapToGrid, placeExit, deleteItem, placeSpy, placeHunter, placePlayer };
enum screenSide { topLeft, bottomLeft, topRight, bottomRight};
class Button
{
protected:
	Graphics *gfx;
	Point position;
	int width;
	int height;
	buttonType type;
	editorMode modeToSwitchTo;
	bool alignWithCamera;
	Point cameraOffSet;
	screenSide ScreenSide;
public:
	Button();
	Button(int _x, int _y, Graphics * gfxi);
	Button(int _x, int _y, int _width, int height, editorMode _mode, Graphics * gfxi);
	Button(int _x, int _y, int _width, int height, editorMode _mode, bool _alignWithCamera, screenSide _ScreenSide, Graphics * gfxi);
	~Button();
	virtual void action();
	virtual void draw();
	Point getPosition();
	buttonType getType();
	int getWidth();
	int getHeight();
	editorMode getEditorMode();
};
extern std::vector<Button*> Buttons;