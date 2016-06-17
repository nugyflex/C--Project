#include "levelEditor.h"
#include <sys/stat.h>
levelEditor::levelEditor(){}
levelEditor::levelEditor(Graphics* _gfx)
{
	gfx = _gfx;
	load();
}
levelEditor::~levelEditor()
{

}
bool levelEditor::doesExist(const char *name) {
		ifstream infile(name);
		return infile.good();
}
void levelEditor::load()
{
	isPlayer = false;
	mode = none;
	snapToGrid = false;
	Buttons.push_back(new Button(20, -80, 100, 20, placePlatform, true, bottomLeft, gfx));
	Buttons.push_back(new Button(20, -40, 100, 20, placeExit, true, bottomLeft, gfx));
	Buttons.push_back(new Button(140, -80, 100, 20, placeSpy, true, bottomLeft, gfx));
	Buttons.push_back(new Button(140, -40, 100, 20, placeHunter, true, bottomLeft, gfx));
	Buttons.push_back(new Button(260, -80, 100, 20, placePlayer, true, bottomLeft, gfx));
	Buttons.push_back(new Button(260, -40, 100, 20, deleteItem, true, bottomLeft, gfx));
	Buttons.push_back(new Button(380, -80, 100, 20, none, true, bottomLeft, gfx));
	Buttons.push_back(new Button(380, -40, 100, 20, toggleSnapToGrid, true, bottomLeft, gfx));
	Buttons.push_back(new Button(500, -80, 100, 20, toggleGrid, true, bottomLeft, gfx));
	snapInterval = 50;
	startOfRect.x = 0;
	showGrid = false;
	itemDeleted = false;
}
void levelEditor::update()
{
	for (int i = 0; i < Buttons.size(); i++)
	{
		if (lastMouseLeft && !mouseLeft && CollisionDetection::checkPointRectIntersect(mousePos, Buttons[i]->getPosition(), Buttons[i]->getWidth(), Buttons[i]->getHeight()))
		{
			if (Buttons[i]->getType() == changemode)
			{
				if (Buttons[i]->getEditorMode() == toggleSnapToGrid)
				{
					if (snapToGrid == true)
					{
						snapToGrid = false;
					}
					else
					{
						snapToGrid = true;
					}
				}
				else
				{
					if (Buttons[i]->getEditorMode() == toggleGrid)
					{
						if (showGrid == true)
						{
							showGrid = false;
						}
						else
						{
							showGrid = true;
						}
					}
					else
					{
						mode = Buttons[i]->getEditorMode();
						startOfRect.x = 0;
					}
				}
			}
			else
			{
				Buttons[i]->action();
			}
			buttonHasBeenCLicked = true;
		}
		
	}
	if (!buttonHasBeenCLicked)
	{
		if (mode == placePlatform || mode == placeExit || mode == placeSpy || mode == placeHunter || mode == placePlayer)
		{
			if (mouseLeft == true && lastMouseLeft == false )
			{
				if (snapToGrid)
				{
					startOfRect = Point{ snapInterval * floor(mousePos.x / snapInterval), snapInterval * floor(mousePos.y / snapInterval) };
				}
				else
				{
					startOfRect = mousePos;
				}
			}
			if (mouseLeft == false && lastMouseLeft == true && startOfRect.x != 0)
			{
				if (mode != placeSpy && mode != placeHunter && mode != placePlayer)
				{
					float tempfloat;
					if (mousePos.x < startOfRect.x)
					{
						tempfloat = mousePos.x;
						mousePos.x = startOfRect.x;
						startOfRect.x = tempfloat;
					}
					if (mousePos.y < startOfRect.y)
					{
						tempfloat = mousePos.y;
						mousePos.y = startOfRect.y;
						startOfRect.y = tempfloat;
					}
				}
				switch (mode)
				{
				case placePlatform:
					if (snapToGrid)
					{
						mousePos.x = snapInterval * floor(mousePos.x / snapInterval);
						mousePos.y = snapInterval * floor(mousePos.y / snapInterval);
						startOfRect.x = snapInterval * floor(startOfRect.x / snapInterval);
						startOfRect.y = snapInterval * floor(startOfRect.y / snapInterval);
					}
						Rects.push_back(new Platform(startOfRect, mousePos.x - startOfRect.x, mousePos.y - startOfRect.y, 0, 0, gfx));
						editorActions.push_back(addRect);
						actionIndexes.push_back(Rects.size() - 1);
					break;
				case placeExit:
					if (snapToGrid)
					{
						mousePos.x = snapInterval * floor(mousePos.x / snapInterval);
						mousePos.y = snapInterval * floor(mousePos.y / snapInterval);
						startOfRect.x = snapInterval * floor(startOfRect.x / snapInterval);
						startOfRect.y = snapInterval * floor(startOfRect.y / snapInterval);
					}
						exitPoints.push_back(new exitPoint(startOfRect, mousePos.x - startOfRect.x, mousePos.y - startOfRect.y, 60, 0, 1));
						editorActions.push_back(addExitPoint);
						actionIndexes.push_back(exitPoints.size() - 1);
					break;
				case placeSpy:
					if (snapToGrid)
					{
						mousePos.x = snapInterval * floor(mousePos.x / snapInterval);
						mousePos.y = snapInterval * floor(mousePos.y / snapInterval);
						startOfRect.x = snapInterval * floor(startOfRect.x / snapInterval);
						startOfRect.y = snapInterval * floor(startOfRect.y / snapInterval);
					}
					if (CollisionDetection::finddistance(mousePos.x, mousePos.x, startOfRect.y, startOfRect.y) < 10)
					{
						Rects.push_back(new Spy(startOfRect, 10, 10, 0, 0, gfx));
					}
					else
					{
						Rects.push_back(new Spy(startOfRect, 10, 10, 0, 0, startOfRect, mousePos, gfx));
					}
					Rects[Rects.size()-1]->load();
					editorActions.push_back(addRect);
					actionIndexes.push_back(Rects.size() - 1);
					break;
				case placeHunter:
					if (snapToGrid)
					{
						mousePos.x = snapInterval * floor(mousePos.x / snapInterval);
						mousePos.y = snapInterval * floor(mousePos.y / snapInterval);
						startOfRect.x = snapInterval * floor(startOfRect.x / snapInterval);
						startOfRect.y = snapInterval * floor(startOfRect.y / snapInterval);
					}
					if (CollisionDetection::finddistance(mousePos.x, mousePos.x, startOfRect.y, startOfRect.y) < 10)
					{
						Rects.push_back(new Hunter(startOfRect, 10, 10, 0, 0, gfx));
					}
					else
					{
						Rects.push_back(new Hunter(startOfRect, 10, 10, 0, 0, startOfRect, mousePos, gfx));
					}
					Rects[Rects.size() - 1]->load();
					editorActions.push_back(addRect);
					actionIndexes.push_back(Rects.size()-1);
					break;
				case placePlayer:
					if (!isPlayer)
					{
						Rects.push_back(new Player(startOfRect, 12, 54, 0, 0, gfx));
						Rects[Rects.size() - 1]->load();
						isPlayer = true;
					}
					editorActions.push_back(addPlayer);
					actionIndexes.push_back(Rects.size() - 1);
					break;
				}
			}
		}
		if (mode == deleteItem && mouseLeft && !lastMouseLeft && !buttonHasBeenCLicked)
		{
			for (int i = Rects.size()-1; i > -1; i--)
			{
				if (CollisionDetection::checkPointRectIntersect(mousePos, Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight()))
				{
					if (Rects[i]->getType() == player)
					{
						isPlayer = false;
						editorActions.push_back(deletePlayer);
						actionIndexes.push_back(i);
					}
					else
					{
						editorActions.push_back(deleteRect);
						actionIndexes.push_back(i);
					}
					rectStatus[i] = false;
					itemDeleted = true;
					break;
				}
			}
			if (!itemDeleted)
			{
				for (int i = exitPoints.size() - 1; i > -1; i--)
				{
					if (CollisionDetection::checkPointRectIntersect(mousePos, exitPoints[i]->getPosition(), exitPoints[i]->getWidth(), exitPoints[i]->getHeight()))
					{
						exitPointStatus[i] = false;
						editorActions.push_back(deleteExitPoint);
						actionIndexes.push_back(i);
						break;
					}
				}
			}
			itemDeleted = false;
		}
	}
	if (eshift)
	{
		if (ekeyA)
		{
			cameraPos.x -= 5;
		}
		if (ekeyD)
		{
			cameraPos.x += 5;
		}
		if (ekeyW)
		{
			cameraPos.y -= 5;
		}
		if (ekeyS)
		{
			cameraPos.y += 5;
		}

	}
	if (econtrol && ekeyS && !lastS)
	{
		saveAsNewLevel();
	}
	//UNDO
	if (econtrol && ekeyZ && !lastZ)
	{
		int size = editorActions.size();
		if (editorActions.size() > 0)
		{
			switch (editorActions[editorActions.size() - 1])
			{
			case deleteRect:
				rectStatus[actionIndexes[actionIndexes.size()-1]] = true;
				break;
			case deletePlayer:
				rectStatus[actionIndexes[actionIndexes.size() - 1]] = true;
				isPlayer = true;
				break;
			case deleteExitPoint:
				exitPointStatus[actionIndexes[actionIndexes.size() - 1]] = true;
				break;
			case addRect:
				rectStatus[actionIndexes[actionIndexes.size() - 1]] = false;
				break;
			case addPlayer:
				rectStatus[actionIndexes[actionIndexes.size() - 1]] = false;
				isPlayer = false;
				break;
			case addExitPoint:
				exitPointStatus[actionIndexes[actionIndexes.size() - 1]] = false;
				break;
			}
			editorActions.erase(editorActions.begin() + editorActions.size()-1);
			actionIndexes.erase(actionIndexes.begin() + actionIndexes.size() - 1);
		}
	}
	lastshift = eshift;
	lastZ = ekeyZ;
	lastS = ekeyS;
	buttonHasBeenCLicked = false;
	while (true)
	{
		if (rectStatus.size() < Rects.size())
		{
			rectStatus.push_back(true);
		}
		else
		{
			break;
		}
	}
	while (true)
	{
		if (exitPointStatus.size() < exitPoints.size())
		{
			exitPointStatus.push_back(true);
		}
		else
		{
			break;
		}
	}
}
void levelEditor::draw()
{
	for (int i = 0; i < Rects.size(); i++)
	{
		if (rectStatus[i] == true)
		{
			Rects[i]->draw();
			if (Rects[i]->getType() == drone)
			{
				if (((Drone*)Rects[i])->getBehaviorType() == patrol)
				{
					gfx->DrawLine(((Drone*)Rects[i])->getPatrolDestination(0), ((Drone*)Rects[i])->getPatrolDestination(1), 1, 0.2, 0.2, 0.7);
				}
			}
		}
	}
	for (int i = 0; i < exitPoints.size(); i++)
	{
		if (exitPointStatus[i] == true)
		{
			gfx->FillRect(exitPoints[i]->getPosition(), exitPoints[i]->getWidth(), exitPoints[i]->getHeight(), 0.5, 1, 0.6, 0.5);
		}
	}
	if (showGrid)
	{
		Point topLeft{ snapInterval*floor((cameraPos.x - (screenWidth/2) - snapInterval)/snapInterval), snapInterval*floor((cameraPos.y - (screenHeight / 2) - snapInterval)/snapInterval) };
		for (int i = 0; i < screenHeight + snapInterval; i++)
		{
			gfx->DrawLine(Point{ topLeft.x, topLeft.y + i*snapInterval }, Point{ topLeft.x + screenWidth + snapInterval*2, topLeft.y + i*snapInterval }, 1, 1, 1, 0.4, 1);
		}
		for (int i = 0; i < screenWidth + snapInterval; i++)
		{
			gfx->DrawLine(Point{ topLeft.x + i*snapInterval, topLeft.y }, Point{ topLeft.x + i*snapInterval, topLeft.y + screenHeight + snapInterval*2 }, 1, 1, 1, 0.2, 1);
		}
	}
	if (snapToGrid)
	{
		gfx->DrawRect(Point{ snapInterval * floor(mousePos.x / snapInterval), snapInterval * floor(mousePos.y / snapInterval) }, 2, 2, 1, 1, 1, 1);
	}
	else
	{
		gfx->DrawRect(mousePos, 2, 2, 1, 1, 1, 1);
	}

	if (mouseLeft && !buttonHasBeenCLicked)
	{
		switch (mode)
		{
		case placePlatform:
			if (snapToGrid)
			{
				gfx->DrawRect(startOfRect, snapInterval * floor(mousePos.x / snapInterval) - startOfRect.x, snapInterval * floor(mousePos.y / snapInterval) - startOfRect.y, 250, 250, 250, 1);
				gfx->FillRect(startOfRect, snapInterval * floor(mousePos.x / snapInterval) - startOfRect.x, snapInterval * floor(mousePos.y / snapInterval) - startOfRect.y, 250, 250, 250, 0.3);
			}
			else
			{
				gfx->DrawRect(startOfRect, mousePos.x - startOfRect.x, mousePos.y - startOfRect.y, 1, 1, 1, 1);
				gfx->FillRect(startOfRect, mousePos.x - startOfRect.x, mousePos.y - startOfRect.y, 0.8, 0.8, 0.8, 0.3);
			}
			break;
		case placeExit:
			if (snapToGrid)
			{
				gfx->DrawRect(startOfRect, snapInterval * floor(mousePos.x / snapInterval) - startOfRect.x, snapInterval * floor(mousePos.y / snapInterval) - startOfRect.y, 250, 250, 250, 1);
				gfx->FillRect(startOfRect, snapInterval * floor(mousePos.x / snapInterval) - startOfRect.x, snapInterval * floor(mousePos.y / snapInterval) - startOfRect.y, 250, 250, 250, 0.3);
			}
			else
			{
				gfx->DrawRect(startOfRect, mousePos.x - startOfRect.x, mousePos.y - startOfRect.y, 0.3, 0.8, 0.4, 1);
				gfx->FillRect(startOfRect, mousePos.x - startOfRect.x, mousePos.y - startOfRect.y, 0.5, 1, 0.6, 0.3);
			}
			break;
		}

	}
}
void levelEditor::saveAsNewLevel()
{
	char tempChar[2000];
	strcpy_s(tempchar, "<?xml version=\"1.0\"?>\n");
	const char* xmlpath = "customMap";

	int counter = 0;
	while (true)
	{
		char charr[20];
		strcpy_s(charr, xmlpath);
		strcat_s(charr, ".xml");
		const char* check = (const char*)charr;
		if (doesExist(check))
		{
			counter++;
			char charInt[20];
			char charTest[30];
			char charTest1[40];
			sprintf_s(charInt, "%d", counter);
			strcpy_s(charTest, charInt);
			strcpy_s(charTest1, xmlpath);
			strcat_s(charTest1, charTest);
			xmlpath = (const char*)charTest1;
		}
		else
		{
			xmlpath = charr;
			break;
		}
	}
	ofstream xmlFile;
	xmlFile.open(xmlpath, fstream::in | fstream::out | fstream::app);
	xmlFile << tempchar;
	xmlFile.close();
	xmlFile.open(xmlpath, fstream::in | fstream::out | fstream::app);
	strcpy_s(tempchar, "");
	for (int i = 0; i < Rects.size(); i++)
	{
		switch (Rects[i]->getType())
		{
		case player:
			addPlayerPositionToXML(Rects[i]);
			break;
		case platform:
			addPlatformToXML(Rects[i]);
			break;
		case drone:
			addDroneToXML((Drone*)Rects[i]);
			break;
		}
	}
	addExitPointToXML(exitPoints[0]);
	char charNP[8];
	char charND[8];
	sprintf_s(charNP, "%d", numberOfPlatforms);
	sprintf_s(charND, "%d", numberOfDrones);
	strcpy_s(tempChar, "<NUMBEROFPLATFORMS>");
	strcat_s(tempchar, tempChar);
	strcat_s(tempchar, charNP);
	strcpy_s(tempChar, "</NUMBEROFPLATFORMS>\n<NUMBEROFDRONES>");
	strcat_s(tempchar, tempChar);
	strcat_s(tempchar, charND);
	strcpy_s(tempChar, "</NUMBEROFDRONES>\n");
	strcat_s(tempchar, tempChar);
	xmlFile << tempchar;
	numberOfDrones = 0;
	numberOfPlatforms = 0;
}
void levelEditor::addPlayerPositionToXML(Rect* _player)
{
	char charX[8];
	sprintf_s(charX, "%d", (int)_player->getPosition().x);
	char charY[8];
	sprintf_s(charY, "%d", (int)_player->getPosition().y);
	char playerchar[500] = "<PLAYERPOS>\n\t<x>";
	char tempChar[100];
	strcat_s(playerchar, charX);
	strcpy_s(tempChar, "</x>\n\t<y>");
	strcat_s(playerchar, tempChar);
	strcat_s(playerchar, charY);
	strcpy_s(tempChar, "</y>\n</PLAYERPOS>\n");
	strcat_s(playerchar, tempChar);
	strcat_s(tempchar, playerchar);
}
void levelEditor::addExitPointToXML(exitPoint* _exitpoint)
{
	char charX[8];
	sprintf_s(charX, "%d", (int)_exitpoint->getPosition().x);
	char charY[8];
	sprintf_s(charY, "%d", (int)_exitpoint->getPosition().y);
	char charWidth[8];
	sprintf_s(charWidth, "%d", (int)_exitpoint->getWidth());
	char charHeight[8];
	sprintf_s(charHeight, "%d", (int)_exitpoint->getHeight());
	char charTimer[8];
	sprintf_s(charTimer, "%d", _exitpoint->getTimer());
	char charForcedxVel[10];
	sprintf_s(charForcedxVel, "%f", _exitpoint->getForcedxVel());
	char charLevel[8];
	sprintf_s(charLevel, "%d", (int)_exitpoint->getLevel());
	char exitChar[500] = "<EXITPOINT>\n\t<x>";
	char tempChar[100];
	strcat_s(exitChar, charX);
	strcpy_s(tempChar, "</x>\n\t<y>");
	strcat_s(exitChar, tempChar);
	strcat_s(exitChar, charY);
	strcpy_s(tempChar, "</y>\n\t<width>");
	strcat_s(exitChar, tempChar);
	strcat_s(exitChar, charWidth);
	strcpy_s(tempChar, "</width>\n\t<height>");
	strcat_s(exitChar, tempChar);
	strcat_s(exitChar, charHeight);
	strcpy_s(tempChar, "</height>\n\t<timer>");
	strcat_s(exitChar, tempChar);
	strcat_s(exitChar, charTimer);
	strcpy_s(tempChar, "</timer>\n\t<forcedxvel>");
	strcat_s(exitChar, tempChar);
	strcat_s(exitChar, charForcedxVel);
	strcpy_s(tempChar, "</forcedxvel>\n\t<level>");
	strcat_s(exitChar, tempChar);
	strcat_s(exitChar, charLevel);
	strcpy_s(tempChar, "</level>\n</EXITPOINT>\n");
	strcat_s(exitChar, tempChar);
	strcat_s(tempchar, exitChar);
}
void levelEditor::addPlatformToXML(Rect* _platform)
{
	char charX[8];
	sprintf_s(charX, "%d", (int)_platform->getPosition().x);
	char charY[8];
	sprintf_s(charY, "%d", (int)_platform->getPosition().y);
	char charWidth[8];
	sprintf_s(charWidth, "%d", (int)_platform->getWidth());
	char charHeight[8];
	sprintf_s(charHeight, "%d", (int)_platform->getHeight());
	char integer_string[4];
	sprintf_s(integer_string, "%d", numberOfPlatforms + 1);
	char platformChar[200] = "<P";
	char tempChar[40];
	strcat_s(platformChar, integer_string);
	strcpy_s(tempChar, ">\n\t<x>");
	strcat_s(platformChar, tempChar);
	strcat_s(platformChar, charX);
	strcpy_s(tempChar, "</x>\n\t<y>");
	strcat_s(platformChar, tempChar);
	strcat_s(platformChar, charY);
	strcpy_s(tempChar, "</y>\n\t<width>");
	strcat_s(platformChar, tempChar);
	strcat_s(platformChar, charWidth);
	strcpy_s(tempChar, "</width>\n\t<height>");
	strcat_s(platformChar, tempChar);
	strcat_s(platformChar, charHeight);
	strcpy_s(tempChar, "</height>\n</P");
	strcat_s(platformChar, tempChar);
	strcat_s(platformChar, integer_string);
	strcpy_s(tempChar, ">\n");
	strcat_s(platformChar, tempChar);
	strcat_s(tempchar, platformChar);
	numberOfPlatforms++;
}
void levelEditor::addDroneToXML(Drone* _drone)
{
	char charX[8];
	sprintf_s(charX, "%d", (int)_drone->getPosition().x);
	char charY[8];
	sprintf_s(charY, "%d", (int)_drone->getPosition().y);
	char charP1x[8];
	char charP1y[8];
	char charP2x[8];
	char charP2y[8];
	if (_drone->getBehaviorType() == patrol)
	{
		sprintf_s(charP1x, "%d", (int)_drone->getPatrolDestination(0).x);
		sprintf_s(charP1y, "%d", (int)_drone->getPatrolDestination(0).y);
		sprintf_s(charP2x, "%d", (int)_drone->getPatrolDestination(1).x);
		sprintf_s(charP2y, "%d", (int)_drone->getPatrolDestination(1).y);
	}
	char charType[8];
	switch (_drone->getDroneType())
	{
	case hunterDrone:
		strcpy_s(charType, "hunter");
		break;
	case spyDrone:
		strcpy_s(charType, "spy");
		break;
	}
	char charWillPatrol[6];
	if (_drone->getBehaviorType() == patrol)
	{
		strcpy_s(charWillPatrol, "true");
	}
	else
	{
		strcpy_s(charWillPatrol, "false");
	}
	char integer_string[4];
	sprintf_s(integer_string, "%d", numberOfDrones + 1);
	char droneChar[200] = "<D";
	char tempChar[40];
	strcat_s(droneChar, integer_string);
	strcpy_s(tempChar, ">\n\t<x>");
	strcat_s(droneChar, tempChar);
	strcat_s(droneChar, charX);
	strcpy_s(tempChar, "</x>\n\t<y>");
	strcat_s(droneChar, tempChar);
	strcat_s(droneChar, charY);
	strcpy_s(tempChar, "</y>\n\t<type>");
	strcat_s(droneChar, tempChar);
	strcat_s(droneChar, charType);
	strcpy_s(tempChar, "</type>\n\t<willPatrol>");
	strcat_s(droneChar, tempChar);
	if (_drone->getBehaviorType() == patrol)
	{
		strcat_s(droneChar, charWillPatrol);
		strcpy_s(tempChar, "</willPatrol>\n\t<P1x>");
		strcat_s(droneChar, tempChar);
		strcat_s(droneChar, charP1x);
		strcpy_s(tempChar, "</P1x>\n\t<P1y>");
		strcat_s(droneChar, tempChar);
		strcat_s(droneChar, charP1y);
		strcpy_s(tempChar, "</P1y>\n\t<P2x>");
		strcat_s(droneChar, tempChar);
		strcat_s(droneChar, charP2x);
		strcpy_s(tempChar, "</P2x>\n\t<P2y>");
		strcat_s(droneChar, tempChar);
		strcat_s(droneChar, charP2y);
		strcpy_s(tempChar, "</P2y>\n</D");
		strcat_s(droneChar, tempChar);
	}
	else
	{
		strcat_s(droneChar, charWillPatrol);
		strcpy_s(tempChar, "</willPatrol>\n</D");
		strcat_s(droneChar, tempChar);

	}
	strcat_s(droneChar, integer_string);
	strcpy_s(tempChar, ">\n");
	strcat_s(droneChar, tempChar);
	strcat_s(tempchar, droneChar);
	numberOfDrones++;
}
