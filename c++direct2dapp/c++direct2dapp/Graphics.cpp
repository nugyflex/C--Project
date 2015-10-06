#include "Graphics.h"



Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
	zoomLevel = 1;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;


	RECT rect;
	GetClientRect(windowHandle, &rect);
	
	factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget);

	if (res != S_OK) return false;
	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;
	brush->SetColor(D2D1::ColorF(0, 0, 0, 0));
	return true;
}
void Graphics::centerCamera(Point _position)
{
	//creating my own matrix for translation
	D2D_MATRIX_3X2_F translation;
	translation._11 = 1; translation._12 = 0.0;
	translation._21 = 0.0; translation._22 = 1;
	translation._31 = -_position.x + 640; translation._32 = -_position.y + 360;
	renderTarget->SetTransform(translation);
}

void Graphics::rotate(Point _position, float _theta)
{
	D2D_MATRIX_3X2_F translation;
	translation._11 = cos(_theta); translation._12 = sin(_theta);
	translation._21 = -1* sin(_theta); translation._22 = cos(_theta);
	translation._31 = -camera.x + 640 + _position.x; translation._32 = -camera.y + 360 + _position.y;
	renderTarget->SetTransform(translation);
}
void Graphics::flip(Point _position, float _theta)
{
	D2D_MATRIX_3X2_F translation;
	translation._11 = -1 * cos(_theta); translation._12 = sin(_theta);
	translation._21 = sin(_theta); translation._22 = cos(_theta);
	translation._31 = -camera.x + 640 + _position.x; translation._32 = -camera.y + 360 + _position.y;
	renderTarget->SetTransform(translation);
}

void Graphics::rotateBack(Point _position, float _theta)
{
	centerCamera(camera);
	//renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(-_theta, D2D1::Point2F(-_position.x - camera.x, -_position.y - camera.y)));
}

void Graphics::ClearScreen(float _r, float _g, float _b)
{
	renderTarget->Clear(D2D1::ColorF(_r, _g, _b));

}
void Graphics::DrawCircle(Point _center, float _radius, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));

	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(_center.x, _center.y), _radius, _radius), brush, 2.0f);
}
void Graphics::DrawRect(Point _position, float _width, float _height, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));
	renderTarget->DrawRectangle(D2D1::Rect(_position.x, _position.y, _position.x+ _width, _position.y + _height), brush, 2.0f);

}

void Graphics::FillRect(Point _position, float _width, float _height, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));
	renderTarget->FillRectangle(D2D1::Rect(_position.x, _position.y, _position.x+ _width, _position.y + _height), brush);
}

void Graphics::DrawLine(Point _position1, Point _position2, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));
	
	renderTarget->DrawLine(D2D1::Point2F(_position1.x, _position1.y), D2D1::Point2F(_position2.x, _position2.y), brush, 2.0f);

}
void Graphics::setZoomLevel(float _zoom)
{
	zoomLevel = _zoom;
}
float Graphics::getZoomLevel()
{
	return zoomLevel;
}
void Graphics::setCamera(Point _p)
{
	camera = _p;
}