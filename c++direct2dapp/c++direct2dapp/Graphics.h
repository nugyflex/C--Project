#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <d2d1effects.h>
#include <d2d1effecthelpers.h>
#include "Common.h"
#include <math.h>


class Graphics //the graphics class, used to draw everything, handles the rendertarget as well
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	ID2D1Bitmap *bitmap;
	ID2D1Bitmap *lightingBitmap;
	ID2D1BitmapRenderTarget *bitmapRenderTarget;
	ID2D1BitmapRenderTarget *lightingTarget;
	ID2D1DeviceContext *deviceContext;
	ID2D1Effect *gaussianBlur;
	ID2D1Effect *pointDefuse;
	int screenShakeX;
	int screenShakeY;
	float screenShakeIntensity;
	float zoomLevel;
	Point camera;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget()
	{
		return bitmapRenderTarget;
	}

	void BeginDraw() { bitmapRenderTarget->BeginDraw(); }
	void EndDraw() { bitmapRenderTarget->EndDraw(); }

	void ClearScreen(float _r, float _g, float _b);
	void DrawCircle(Point _center, float _radius, float _r, float _g, float _b, float _a);
	void DrawRect(Point _position, float _width, float _height, float _r, float _g, float _b, float _a);
	void FillRect(Point _position, float _width, float _height, float _r, float _g, float _b, float _a);
	void DrawLine(Point _position1, Point _position2, float _r, float _g, float _b, float _a);
	void centerCamera(Point _position);
	void setZoomLevel(float _zoom);
	float getZoomLevel();
	void rotate(Point _position, float _theta);
	void setCamera(Point _p);
	void rotateBack(Point _position, float _theta);
	void flip(Point _position, float _theta);
	void draw();
	void setScreenShakeIntensity(float _intensity);
	void setScreenShake(float _intensity);
	void settleScreenShake();
	void screenShake();
};