#pragma once
#include "Graphics.h"

class Button
{
protected:
	Graphics *gfx;
	Point position;
public:
	Button();
	Button(int _x, int _y, Graphics * gfxi);
	~Button();
	virtual void action();
	virtual void draw();
	Point getPosition();
};