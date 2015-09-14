#include <Windows.h>
#include <vector>
#include "Graphics.h"

#include "Level1.h"
#include "GameController.h"
#include "Camera.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


Graphics* graphics;
Camera* camera;


void sleep(int _mseconds)
{
	if (_mseconds > 0)
	{
		clock_t goal = _mseconds + clock();
		while (goal > clock());
	}
}




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
	vector<Rect*> Rects;
	graphics = new Graphics();
	Point randompoint = { 50, 9 };
	Rect* tempobject = new Player(randompoint, 32, 54, 0, 0, graphics);
	Rects.push_back(tempobject);
	randompoint = { 50, 298 };
	tempobject = new Platform(randompoint, 1200, 50, 0, 0, graphics);
	Rects.push_back(tempobject);
	randompoint = { 50, 500 };
	tempobject = new Platform(randompoint, 1600, 50, 0, 0, graphics);
	Rects.push_back(tempobject);

	/*for (int i = 1; i < 2500; i++)
	{
		Rects.push_back(Rect(randompoint, 400, 50, 0, 0, true, graphics));
	}*/
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

	GameController::fps = 60;
	ShowWindow(windowhandle, nCmdShow);
	GameController::LoadInitialLevel(new Level1());
	GameController::zoomLevel = 1;
	MSG message;
	message.message = WM_NULL;
	int starttime = 0;
	int endtime = 0;
	float endminusstart = 0;
	Rects[0]->load();
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			starttime = clock();
			camera->calcNewPos(Rects[0]->getPosition());
			GameController::Update(Rects);
			graphics->BeginDraw();
			graphics->centerCamera(camera->getPosition());
			GameController::Render(Rects);
			//graphics->FillRect(camera->getPosition(), 10, 10, 1, 1, 1, 1);
			endtime = clock();
			endminusstart = endtime - starttime;
			randompoint = { 26,26 };
			graphics->FillRect(randompoint, 108, 18, 0.2, 0.2, 0.2, 1);
			randompoint = { 30,30 };
			graphics->FillRect(randompoint, 100, 10, 0.5, 0.5, 0.5, 1);
			randompoint = { 30,30 };
			if (endminusstart / (1000 / GameController::fps) < 0.5)
			{
				graphics->FillRect(randompoint, 100 * (endminusstart / (1000 / GameController::fps)), 10, 0.5, 1, 0.5, 1);
			}
			else
			{
				graphics->FillRect(randompoint, 100 * (endminusstart / (1000 / GameController::fps)), 10, 1, 0.5, 0.5, 1);
				if (endminusstart / (1000 / GameController::fps) > 1)
				{
					graphics->FillRect(randompoint, 100 * (endminusstart / (1000 / GameController::fps)), 10, 1, 0.2, 0.2, 1);
				}
			}
			graphics->EndDraw();

			if (1000 / GameController::fps - endminusstart > 1)
			{
				sleep(1000 / GameController::fps - endminusstart);
			}
		}
	}

	delete graphics;
	return 0;
}