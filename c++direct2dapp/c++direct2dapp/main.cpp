#include <Windows.h>
#include "Graphics.h"

#include "Level1.h"
#include "GameController.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect{ 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "c++ things", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left , rect.bottom - rect.top, NULL, NULL, hInstance, 0);

if (!windowhandle) return -1;

graphics = new Graphics();

if (!graphics->Init(windowhandle))
{
	delete graphics;
	return -1;
}

GameLevel::Init(graphics);

ShowWindow(windowhandle, nCmdShow);

GameController::LoadInitialLevel(new Level1());

MSG message;
message.message = WM_NULL;
while (message.message != WM_QUIT)
{
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		DispatchMessage(&message);
	else
	{

		GameController::Update();



		graphics->BeginDraw();
		GameController::Render();
		graphics->EndDraw();
	}
}

/*
MSG message;
while(GetMessage(&message, NULL, 0, 0))
	{
	DispatchMessage(&message);
	}*/
	delete graphics;
	return 0;
}