#include <Windows.h>
#include <vector>
#include "Graphics.h"

#include "Level1.h"
#include "level2.h"
#include "Level3.h"
#include "editorLevel.h"
#include "menu.h"
#include "gameController.h"
#include "Camera.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include "stdio.h"
#include <stdlib.h>
#include "psapi.h"
#include <fstream>
#include <string>
#include "Dsound.h"
#include "tinyxml2.h"
using namespace tinyxml2;
using namespace std;

#define DIV 1048576
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
Graphics* graphics;
Camera* camera;
RECT rect;

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
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN: //This is used if we press a key
		switch (LOWORD(wParam))
		{
		case 0x57:
			gameController::keyW = true;
			break;
		case 0x41:
			gameController::keyA = true;
			break;
		case 0x53:
			gameController::keyS = true;
			break;
		case 0x44:
			gameController::keyD = true;
			break;
		case 0x51:
			gameController::keyQ = true;
			break;
		case 0x5A:
			gameController::keyZ = true;
			break;
		case VK_SPACE:
			gameController::space = true;
			break;
		case VK_SHIFT:
			gameController::shift = true;
			break;
		case VK_CONTROL:
			gameController::control = true;
			break;
		}
		break;
	case WM_KEYUP: //This is used if we release a key
		switch (LOWORD(wParam))
		{
		case 0x57:
			gameController::keyW = false;
			break;
		case 0x41:
			gameController::keyA = false;
			break;
		case 0x53:
			gameController::keyS = false;
			break;
		case 0x44:
			gameController::keyD = false;
			break;
		case 0x51:
			gameController::keyQ = false;
			break;
		case 0x5A:
			gameController::keyZ = false;
			break;
		case VK_SPACE:
			gameController::space = false;
			break;
		case VK_SHIFT:
			gameController::shift = false;
			break;
		case VK_CONTROL:
			gameController::control = false;
			break;
		case VK_ESCAPE:
			if (paused)
			{
				paused = false;
			}
			else
			{
				paused = true;
			}
			break;
		}
		break;
	case WM_MOUSEMOVE: //this sets the cursor when the mouse is moved.
		gameController::setMouseX(LOWORD(lParam));
		gameController::setMouseY(HIWORD(lParam));
		gameController::mouse.x += cameraPos.x - screenWidth / 2;
		gameController::mouse.y += cameraPos.y - screenHeight / 2;
	case WM_LBUTTONDOWN:
		switch (LOWORD(wParam))
		{
		case MK_LBUTTON:
			gameController::mouseLeft = true;
			break;
		}
		break;
	case WM_LBUTTONUP:

		gameController::mouseLeft = false;

		break;
	}
	//GetWindowRect(hwnd, &rect);

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
//----------------LOOK-HERE!-------------//
// the .h files are header files, they   ||
// contain the declarations of the       ||
// classes and their methods and         ||
// properties, the cpp files contain the ||
// actual code for those methods defined ||
// in the header file.                   ||
//=======================================//

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) //same as int main in normal c++, the first code run in the program
{
	vector<Point> temppoints;
	graphics = new Graphics();
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&windowclass);
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	RECT rect;
	screenWidth = desktop.right;
	screenHeight = desktop.bottom - 70;
	rect = { 0, 0, screenWidth, screenHeight };

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "c++ things", WS_OVERLAPPEDWINDOW, 0, 0, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}
	//initialising and loading some stuff and setting the framerate
	gameLevel::Init(graphics);
	gameController::fps = 60;
	ShowWindow(windowhandle, nCmdShow);
	gameController::LoadInitialLevel(new Menu());
	gameController::zoomLevel = 1;
	MSG message;
	message.message = WM_NULL;
	int starttime = 0;
	int endtime = 0;
	float endminusstart = 0;
	

	Point randompoint = { 0,0 };
	gameController::mouse = randompoint;
	//===========||TODO||=============///
	// 1. XML                         |x|
	//================================///
	// 2. Level editor                | |
	//================================///
	// 3. Audio                       | |
	//================================///
	// 4. Networking                  | |
	//================================///
	// 5. Direct 3D                   | |
	//================================///


	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			starttime = clock();

			mousePos = gameController::mouse;
			mouseLeft = gameController::mouseLeft;

			graphics->setCamera(cameraPos);
			//handling input
			gameController::HandleInput();
			//updating everything
			gameController::Update();
			lastMouseLeft = mouseLeft;
			graphics->BeginDraw();
			graphics->centerCamera(cameraPos);
			
			//drawing everything
			gameController::Render();
			//theLevelEditor.draw();
			graphics->settleScreenShake();
			graphics->screenShake();

			temppoints.clear();
			endtime = clock();
			endminusstart = endtime - starttime;
			// resource/time use display ----------
			
			randompoint = { 26,26 };
			graphics->FillRect(randompoint, 108, 18, 0.2, 0.2, 0.2, 1);
			randompoint = { 30,30 };
			graphics->FillRect(randompoint, 100, 10, 0.5, 0.5, 0.5, 1);
			randompoint = { 30,30 };
			
			if (endminusstart / (1000 / gameController::fps) < 0.5)
			{
				graphics->FillRect(randompoint, 100 * (endminusstart / (1000 / gameController::fps)), 10, 0.5, 1, 0.5, 1);
			}
			else
			{
				graphics->FillRect(randompoint, 100 * (endminusstart / (1000 / gameController::fps)), 10, 1, 0.5, 0.5, 1);
				if (endminusstart / (1000 / gameController::fps) > 1)
				{
					graphics->FillRect(randompoint, 100 * (endminusstart / (1000 / gameController::fps)), 10, 1, 0.2, 0.2, 1);
				}
			}
			
			//-------------------------------------
			graphics->EndDraw();
			graphics->draw();
			//so it runs at the set framerate, it sleeps for the rest of the time allocated to complete the frame
			if (1000 / gameController::fps - endminusstart > 1)
			{
				sleep(1000 / gameController::fps - endminusstart);
			}
		}
	}
	exit(0);
	delete graphics;
	return 0;
}