#include <Windows.h>
#include <vector>
#include "Graphics.h"

#include "Level1.h"
#include "GameController.h"
#include "Camera.h"


using namespace std;


Graphics* graphics;
Camera* camera;





LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }

	switch (uMsg)
	{

	case WM_KEYDOWN: //This is used if we press a key
		switch (LOWORD(wParam))
		{
		case 0x57:
			GameController::keyW = true;
			break;

		case 0x41:
			GameController::keyA = true;
			break;

		case 0x53:
			GameController::keyS = true;
			break;

		case 0x44:
			GameController::keyD = true;
			break;
		}
		break;
	case WM_KEYUP: //This is used if we release a key
		switch (LOWORD(wParam))
		{
		case 0x57:
			GameController::keyW = false;
			break;

		case 0x41:
			GameController::keyA = false;
			break;

		case 0x53:
			GameController::keyS = false;
			break;

		case 0x44:
			GameController::keyD = false;
			break;
		}
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	vector<Rect> Rects;
	graphics = new Graphics();
	Point randompoint = {50, 9 };
	Rects.push_back(Rect(randompoint, 30, 30, 0, 0, false, graphics));
	randompoint = { 50, 300 };
	Rects.push_back(Rect(randompoint, 400, 50, 0, 0, true, graphics));
	randompoint = { 50, 500 };
	Rects.push_back(Rect(randompoint, 400, 50, 0, 0, true, graphics));
	camera = new Camera(randompoint);

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



	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics);

	ShowWindow(windowhandle, nCmdShow);

	GameController::LoadInitialLevel(new Level1());
	GameController::zoomLevel = 1;
	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{

			camera->calcNewPos(Rects[0].getPosition());
			GameController::Update(Rects);
			graphics->BeginDraw();

			graphics->centerCamera(camera->getPosition());
			//graphics->zoomCamera(GameController::zoomLevel);
			GameController::Render(Rects);
			graphics->EndDraw();
		}
	}

	delete graphics;
	return 0;
}