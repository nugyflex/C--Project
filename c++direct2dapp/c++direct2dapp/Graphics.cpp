#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	bitmapRenderTarget = NULL;
	lightingTarget = NULL;
	brush = NULL;
	zoomLevel = 1;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (bitmapRenderTarget) bitmapRenderTarget->Release();
	if (lightingTarget) lightingTarget->Release();
	if (brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget);
	renderTarget->CreateCompatibleRenderTarget(&bitmapRenderTarget);
	renderTarget->CreateCompatibleRenderTarget(&lightingTarget);
	if (res != S_OK) return false;
	res = bitmapRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	res = lightingTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
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
	translation._31 = -_position.x + screenWidth / 2 + screenShakeX; translation._32 = -_position.y + screenHeight / 2 + screenShakeY;
	bitmapRenderTarget->SetTransform(translation);
}

void Graphics::rotate(Point _position, float _theta)
{
	D2D_MATRIX_3X2_F translation;
	translation._11 = cos(_theta); translation._12 = sin(_theta);
	translation._21 = -1 * sin(_theta); translation._22 = cos(_theta);
	translation._31 = -camera.x + screenWidth / 2 + _position.x + screenShakeX; translation._32 = -camera.y + screenHeight / 2 + _position.y + screenShakeY;
	bitmapRenderTarget->SetTransform(translation);
}
void Graphics::flip(Point _position, float _theta)
{
	D2D_MATRIX_3X2_F translation;
	translation._11 = -1 * cos(_theta); translation._12 = sin(_theta);
	translation._21 = sin(_theta); translation._22 = cos(_theta);
	translation._31 = -camera.x + screenWidth / 2 + _position.x + screenShakeX; translation._32 = -camera.y + screenHeight / 2 + _position.y + screenShakeY;
	bitmapRenderTarget->SetTransform(translation);
}

void Graphics::rotateBack(Point _position, float _theta)
{
	centerCamera(camera);
	//renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(-_theta, D2D1::Point2F(-_position.x - camera.x, -_position.y - camera.y)));
}

void Graphics::ClearScreen(float _r, float _g, float _b)
{
	bitmapRenderTarget->Clear(D2D1::ColorF(_r, _g, _b));
}
void Graphics::DrawCircle(Point _center, float _radius, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));

	bitmapRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(_center.x, _center.y), _radius, _radius), brush, 2.0f);
}
void Graphics::DrawRect(Point _position, float _width, float _height, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));
	bitmapRenderTarget->DrawRectangle(D2D1::Rect(_position.x, _position.y, _position.x + _width, _position.y + _height), brush, 2.0f);
}

void Graphics::FillRect(Point _position, float _width, float _height, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));
	bitmapRenderTarget->FillRectangle(D2D1::Rect(_position.x, _position.y, _position.x + _width, _position.y + _height), brush);
}

void Graphics::DrawLine(Point _position1, Point _position2, float _r, float _g, float _b, float _a)
{
	brush->SetColor(D2D1::ColorF(_r, _g, _b, _a));
	bitmapRenderTarget->DrawLine(D2D1::Point2F(_position1.x, _position1.y), D2D1::Point2F(_position2.x, _position2.y), brush, 2.0f);
	if (_position2.x < 100)
	{
		bitmapRenderTarget->DrawLine(D2D1::Point2F(_position1.x, _position1.y), D2D1::Point2F(_position2.x, _position2.y), brush, 2.0f);
	}
	if (_position1.x == 0)
	{
		bitmapRenderTarget->DrawLine(D2D1::Point2F(_position1.x, _position1.y), D2D1::Point2F(_position2.x, _position2.y), brush, 2.0f);
	}
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
void Graphics::draw()
{
	renderTarget->QueryInterface(&deviceContext);

	// Create and apply gaussian blur
	//deviceContext->CreateEffect(CLSID_D2D1Brightness, &gaussianBlur);

	bitmapRenderTarget->GetBitmap(&bitmap);
	//normal drawing
	renderTarget->BeginDraw();
	renderTarget->DrawBitmap(bitmap, D2D1::RectF(0, 0, screenWidth, screenHeight), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, screenWidth, screenHeight));
	renderTarget->EndDraw();
}
void Graphics::setScreenShakeIntensity(float _intensity)
{
	screenShakeIntensity = _intensity;
}
void Graphics::setScreenShake(float _intensity)
{
	if (_intensity == 0)
	{
		screenShakeX = 0;
		screenShakeY = 0;
	}
	else
	{
		float amount = _intensity * 80;
		if (amount < 1) { amount = 1; }
		screenShakeX = -(amount / 2) + (rand() % (int)amount + 1);
		screenShakeY = -(amount / 2) + (rand() % (int)amount + 1);
	}
}
void Graphics::settleScreenShake()
{
	if (screenShakeIntensity > 0)
	{
		screenShakeIntensity = screenShakeIntensity - 0.01;
	}
	if (screenShakeIntensity < 0)
	{
		screenShakeIntensity = 0;
	}
	if (screenShakeIntensity < 1 / 80)
	{
		screenShakeIntensity = 0;
	}
}
void Graphics::screenShake()
{
	float result = floor(screenShakeIntensity * 100) / 100;
	setScreenShake(result);
}