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



//handle all window events like keypress, mouse movement and pressing the red x
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
	case WM_MOUSEMOVE: //this sets the cursor when the mouse is moved.
		GameController::setMouseX(LOWORD(lParam));
		GameController::setMouseY(HIWORD(lParam));
GameController::mouse.x += camera->getPosition().x - 1280 / 2;
GameController::mouse.y += camera->getPosition().y - 360;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	vector<Point> temppoints;
	vector<Rect*> Rects;
	graphics = new Graphics();
	Point randompoint = { 640, 9 };
	Rect* tempobject = new Player(randompoint, 32, 54, 0, 0, graphics);
	Rects.push_back(tempobject);
	randompoint = { 50, 298 };
	tempobject = new Platform(randompoint, 1200, 50, 0, 0, graphics);
	Rects.push_back(tempobject);
	randompoint = { 50, 500 };
	tempobject = new Platform(randompoint, 1600, 50, 0, 0, graphics);
	Rects.push_back(tempobject);
	randompoint = { 500, 450 };
	tempobject = new Platform(randompoint, 50, 50, 0, 0, graphics);
	Rects.push_back(tempobject);
	randompoint = { 200, 200 };
	tempobject = new FireBall(randompoint, 0, 0, graphics);
	Rects.push_back(tempobject);
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

	RECT rect{ 0, 0, 1280, 720 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "c++ things", WS_OVERLAPPEDWINDOW, 0, 0, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);



	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}
	//initialising and loading some stuff and setting the framerate
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
	Rects[4]->load();
	GameController::mouse = randompoint;

	SpriteSheet background = SpriteSheet(L"sanddunes2.png", 1280, 720, 0, 0, graphics);
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			//makes the mouse movie with the camera
			GameController::mouse.x += camera->getxVel();
			GameController::mouse.y += camera->getyVel();

			starttime = clock();
			camera->calcNewPos(Rects[0]->getPosition());
			//updating everything
			GameController::Update(Rects);
			graphics->BeginDraw();
			graphics->centerCamera(camera->getPosition());
			background.Draw(0, camera->getPosition().x - 640, camera->getPosition().y - 360);
			//drawing objects
			GameController::Render(Rects);

			if (CollisionDetection::checkRectLineIntersect(Rects[1]->getPosition(), Rects[1]->getWidth(), Rects[1]->getHeight(), GameController::mouse, Rects[0]->getPosition()))
			{
				graphics->DrawLine(Rects[0]->getPosition(), GameController::mouse, 1, 0, 0, 1);
			}
			else
			{
				graphics->DrawLine(Rects[0]->getPosition(), GameController::mouse, 0, 1, 0, 1);
			}

			for (int i = 0; i < Rects.size(); i++)
			{
				if (Rects[i]->getType() == platform)
				{
					if (CollisionDetection::checkRectLineIntersect(Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight(), GameController::mouse, Rects[0]->getPosition()))
					{
						Point test = CollisionDetection::getClosestRectLineIntersect(Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight(), GameController::mouse, Rects[0]->getPosition());
						temppoints.push_back(test);
					}
				}
			}
			for (int i = 0; i < temppoints.size(); i++)
			{
				graphics->DrawRect(temppoints[i], 10, 10, 1, 0, 0, 1);
			}
			for (int i = 0; i < Rects.size(); i++)
			{
				if (Rects[i]->getType() == platform)
				{
					if (CollisionDetection::checkRectLineIntersect(Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight(), GameController::mouse, Rects[0]->getPosition()))
					{
						graphics->DrawRect(CollisionDetection::getClosestPoint(Rects[0]->getPosition(), temppoints), 10, 10, 1, 1, 1, 1);
						
					}
				}
			}

			temppoints.clear();
			endtime = clock();
			endminusstart = endtime - starttime;
			randompoint = { 26,26 };
			graphics->FillRect(randompoint, 108, 18, 0.2, 0.2, 0.2, 1);
			randompoint = { 30,30 };
			graphics->FillRect(randompoint, 100, 10, 0.5, 0.5, 0.5, 1);
			randompoint = { 30,30 };

			// resource/time use display ----------
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
			//-------------------------------------
			graphics->EndDraw();
			//so it runs at the set framerate, it sleeps for the rest of the time allocated to complete the frame
			if (1000 / GameController::fps - endminusstart > 1)
			{
				sleep(1000 / GameController::fps - endminusstart);
			}
		}
	}

	delete graphics;
	return 0;
}