#pragma once

#include <Windows.h>
#include <d2d1.h>
#include "Common.h"
#include <math.h>

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
	float zoomLevel;
	Point camera;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

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
};