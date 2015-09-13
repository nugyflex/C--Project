#pragma once

#include <wincodec.h>
#include "Graphics.h"

class SpriteSheet
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;
	int frameWidth;
	int frameHeight;
	int frame;
	int fc;
	int frames;
	int speed;//Frame changes per second
public:
	SpriteSheet(wchar_t* filename, int _frameWidth, int _frameHeight, int _frame, int _frames, Graphics* gfx);
	SpriteSheet();
	~SpriteSheet();

	void Draw(int _frame, float _x, float _y);
	void autoSwitchFrame(int _speed);
	void nextFrame();
	void setFrame(int _frame);
};