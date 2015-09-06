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
public:
	SpriteSheet(wchar_t* filename, int _frameWidth, int _frameHeight, int _frame, Graphics* gfx);

	~SpriteSheet();

	void Draw(int _frame, float _x, float _y);
};