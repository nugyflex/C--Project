#include "playableLevel.h"
#include <stdio.h>
#include <math.h>
#include <string>

void playableLevel::loadObjects()
{
}
void playableLevel::Load() //loads the level, called when the level is instantiated
{
	//LevelEditor = levelEditor(gfx);////
	qLatch = false;
	projectiles = new projectileCollection(gfx);
	particles = new particleCollection(gfx);
	Button* temp = new MenuButton(0, 0, gfx);
	Buttons.push_back(temp);
	temp = new ExitButton(0, 100, gfx);
	Buttons.push_back(temp);
	boundaryIn.x = -100000;
	boundaryIn.y = -100000;
	boundaryOut.x = 100000;
	boundaryOut.y = 100000;
	loadObjects();
	Rects.push_back(new Player(getPlayerPositionFromXML(), 12, 54, 0, 0, gfx));
	Gun* newgun = new assaultRifle(300, 300, gfx);
	weapons.push_back(newgun);
	weapons[0]->load();
	weapons[0]->setParent(true);
	((Player*)Rects[0])->addWeapon(weapons[0]);
	camera = new Camera(Point{ 0,0 });

	for (int i = 0; i < weapons.size(); i++)
	{
		weapons[i]->load();
	}
	playerIndex = -1;
	for (int i = 0; i < Rects.size(); i++)
	{
		if (Rects[i]->getType() == player)
		{
			playerIndex = i;
		}
	}
	if (playerIndex != -1)
	{
		camera->calcNewPos(Rects[playerIndex]->getPosition(), boundaryIn, boundaryOut);
	}
	cameraPos = camera->getPosition();
	gfx->centerCamera(cameraPos);
	addAllPlatformsFromXML();
	addAllDronesFromXML();
	addExitPointFromXML(doc.FirstChildElement("EXITPOINT"));
	//loads all Rectangles
	for (int i = 0; i < Rects.size(); i++)
	{
		Rects[i]->load();
	}
}

void playableLevel::Unload() { //called when the level is finishded
	delete backGround;
	delete camera;
	for (int i = 0; i < Buttons.size(); i++)
	{
		delete Buttons[i];
	}
	Buttons.clear();
	for (auto it = Rects.begin(); it != Rects.end(); ++it) {
		delete *it;
	}
	Rects.clear();
	delete particles;
	exitPoints.clear();
}
void playableLevel::HandleInput()
{
	if (paused)
	{
		for (int i = 0; i < Buttons.size(); i++)
		{
			if (!lastMouseLeft && mouseLeft && CollisionDetection::checkPointRectIntersect(mousePos, Point{ Buttons[i]->getPosition().x + cameraPos.x, Buttons[i]->getPosition().y + cameraPos.y }, 100, 50))
			{
				Buttons[i]->action();
			}
		}
	}
	else
	{
		if (playerIndex == -1 && gameController::space == true)
		{
			playerIndex = Rects.size();
			Rects.push_back(new Player(getPlayerPositionFromXML(), 12, 54, 0, 0, gfx));
			Rects[playerIndex]->load();
			((Player*)Rects[playerIndex])->addWeapon(weapons[0]);
		}
		if (playerIndex != -1)
		{
			//makes the mouse movie with the camera
			gameController::mouse.x += camera->getxVel();
			gameController::mouse.y += camera->getyVel();
			//=================CONTROLS==============//
			//VARIABLE JUMP
			if (gameController::keyW)
			{
				if (Rects[playerIndex]->getyVel() >= 0)
				{
					for (int j = 0; j < Rects.size(); j++)
					{
						if (Rects[j]->getFixed() && CollisionDetection::getSide(Rects[playerIndex], Rects[j]) == 4)
						{
							if (((Player*)Rects[playerIndex])->getCrouched()) { Rects[playerIndex]->setyVel(-4); }
							else {
								Rects[playerIndex]->setyVel(-8);
							}

						}
					}
				}

			}
			else
			{
				if (Rects[playerIndex]->getyVel() < -3)
				{
					Rects[playerIndex]->setyVel(-3);
				}
			}
			if (gameController::keyQ)
			{
				if (qLatch)
				{
					float theta = atan(-1 * (mousePos.y - Rects[playerIndex]->getPosition().y) / (mousePos.x - Rects[playerIndex]->getPosition().x));
					float xVel;
					float yVel;
					if (mousePos.x > Rects[playerIndex]->getPosition().x) {
						yVel = sin(theta) * -1 * 8;
						xVel = cos(theta) * 8;
					}
					else {
						yVel = sin(theta) * 8;
						xVel = cos(theta) * -1 * 8;
					}
					Rects.push_back(new Grenade(Rects[playerIndex]->getPosition(), xVel, yVel - 5, 120, gfx));
				}
				qLatch = false;
			}
			else
			{
				qLatch = true;
			}
			if (gameController::shift)
			{
				((Player*)Rects[playerIndex])->setVel(5);
			}
			else
			{
				((Player*)Rects[playerIndex])->setVel(3);
			}
			if (((Player*)Rects[playerIndex])->getCrouched())
			{
				((Player*)Rects[playerIndex])->setVel(1.5);
			}
			if (gameController::keyA)
			{
				Rects[playerIndex]->setxVel(-((Player*)Rects[playerIndex])->getVel());
			}
			if (gameController::keyD)
			{
				Rects[playerIndex]->setxVel(((Player*)Rects[playerIndex])->getVel());
			}
			if (!gameController::keyA && !gameController::keyD)
			{
				Rects[playerIndex]->setxVel(0);
			}


			if (gameController::keyA && gameController::keyD)
			{
				Rects[playerIndex]->setxVel(0);
			}
			if (gameController::keyS)
			{
				((Player*)Rects[playerIndex])->setCrouched(true);
			}
			else
			{
				((Player*)Rects[playerIndex])->setCrouched(false);
			}
			//==============END OF CONTROLS===========//
			//==CHECKING IF THE PLAYER IS AT AN EXIT POINT==//
			for (int i = 0; i < exitPoints.size(); i++)
			{
				if (CollisionDetection::CheckRectangleIntersect(Rects[playerIndex], exitPoints[i]->getPosition(), exitPoints[i]->getWidth(), exitPoints[i]->getHeight()))
				{
					exitPoints[i]->activate((Player*)Rects[playerIndex]);
				}
			}
		}
	}
}
void playableLevel::Update() //updates all physics, controls and collision detection (and more!)
{
	if (!paused)
	{
		playerIndex = -1;
		for (int i = 0; i < Rects.size(); i++)
		{
			if (Rects[i]->getType() == player)
			{
				playerIndex = i;
			}
		}


		if (playerIndex != -1)
		{
			camera->calcNewPos(Rects[playerIndex]->getPosition(), boundaryIn, boundaryOut);
			
		}
		cameraPos = camera->getPosition();
		//===SHOOTING WITH HITSCAN==//
		if (gameController::mouseLeft)
		{
			if (playerIndex != -1)
			{
				if (((Player*)Rects[playerIndex])->weapons.size() > 0 && !((Player*)Rects[playerIndex])->getSprinting())
				{
					Point temppoint = CollisionDetection::getClosestTarget(((Player*)Rects[playerIndex])->getWeaponPos(), CollisionDetection::projectLineToEdge(cameraPos, ((Player*)Rects[playerIndex])->getWeaponPos(), mousePos));
					if (((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->getCooldown() < -2 && ((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->getCanFire())
					{
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
						particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) - 3 }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
					}
					
					if (((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->fire())
					{
						if (((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->getLatch())
						{
							((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->setFireLatch(false);
						}
						//particles->add(shell, Point { Rects[i]->getPosition().x + Rects[i]->getWeaponOffsetX(), Rects[i]->getPosition().y + Rects[i]->getWeaponOffsetY()}, -1 + (rand() % 2 + 1), -6 + (rand() % 2 + 1));
						float test = rand() % 10 + 1;
						if (test > 9)
						{
							test = rand() % 10 + 5;
						}
						else
						{
							if (test > 2)
							{
								test = rand() % 2 + 1;
							}
							else
							{
								test = 0;
							}
						}
						for (int i = 0; i < test; i++)
						{
							particles->add(smoke, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) });
							if (rand() % 10 + 1 > 6)
							{
								particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);
							}
						}
						for (int j = 0; j < Rects.size(); j++)
						{
							if (Rects[j]->getType() == drone)
							{
								Rect* testRect;
								testRect = new Rect(Point{ temppoint.x - 2, temppoint.y - 1 }, 3, 3, 0, 0, true, drone, false, gfx);
								if (CollisionDetection::CheckRectangleIntersect(Rects[j], testRect))
								{
									((Spy*)Rects[j])->subtractHealth(((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->getDamage());
									if (((Spy*)Rects[j])->getHealth() < 1)
									{
										temppoint = Rects[j]->getPosition();
										//Rects.push_back(new Spy(Point{ 220, 220 }, 10, 10, 0, 0, Point{ 100, 220 }, Point{ 400, 220 }, gfx));
										switch (((Drone*)Rects[j])->getDroneType())
										{
										case spyDrone:
											gfx->setScreenShakeIntensity(0.3);
											break;
										case hunterDrone:
											gfx->setScreenShakeIntensity(0.6);
											break;
										}
										Rects.erase(Rects.begin() + j);
										if (j < playerIndex)
										{
											playerIndex--;
										}

										//Rects[Rects.size() - 1]->load();

										for (int l = 0; l < 20; l++)
										{
											particles->add(spark, temppoint, -5 + (rand() % 10 + 1), -10 + (rand() % 20 + 1));
										}
										for (int l = 0; l < 25; l++)
										{
											particles->add(smoke, Point{ temppoint.x - 35 + (rand() % 70 + 1), temppoint.y - 35 + (rand() % 70 + 1) });
										}
									}
								}
								delete testRect;
							}
						}
					}
					if (((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->getLatch())
					{
						((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->setFireLatch(false);

					}
				}
			}
		}
		else
		{
			if (playerIndex != -1)
			{
				if (((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->getLatch())
				{

					if (((Player*)Rects[playerIndex])->weapons.size() > 0)
					{

						((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->setFireLatch(true);
					}
				}
			}
		}

		for (int i = 0; i < Rects.size(); i++)
		{
			//==GRAVITY==//
			if (Rects[i]->getGravity())
			{
				Rects[i]->setyVel(Rects[i]->getyVel() + 0.51f);
			}
			//adding xvel x to x and yvel to y
			if (Rects[i]->getType() == drone && playerIndex != -1)
			{
				Rects[i]->calcNewPos(Point{ Rects[playerIndex]->getPosition().x + Rects[playerIndex]->getWeaponOffsetX(), Rects[playerIndex]->getPosition().y + Rects[playerIndex]->getWeaponOffsetY()
				});
			}
			Rects[i]->calcNewPos();
			if (!Rects[i]->getFixed() && Rects[i]->getType() != grenade)
			{
				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getFixed())
					{
						CollisionDetection::correctPosition(Rects[i], Rects[j]);
					}
				}
			}
			if (Rects[i]->getType() == grenade)
			{
				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getFixed())
					{
						CollisionDetection::correctPositionBounce(Rects[i], Rects[j], 0.6, 0.4);
					}
				}
				if (((Grenade*)Rects[i])->getTimer() < 1)
				{
					
					gfx->setScreenShakeIntensity(0.5);
					for (int l = 0; l < 40; l++)
					{
						particles->add(spark, Rects[i]->getPosition(), -10 + (rand() % 20 + 1), -15 + (rand() % 30 + 1));
					}
					for (int l = 0; l < 15; l++)
					{
						particles->add(smoke, Point{ Rects[i]->getPosition().x - 35 + (rand() % 70 + 1), Rects[i]->getPosition().y - 35 + (rand() % 70 + 1) });
					}
					explosion* TestExplosion = new explosion(100, 10, Rects[i]->getPosition());
					if (i < playerIndex)
					{
						playerIndex--;
					}
					Rects.erase(Rects.begin() + i);
					i--;
				}
			}
			if (Rects[i]->getType() == drone)
			{
				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getType() == drone && j != i)
					{
						CollisionDetection::correctPosition(Rects[i], Rects[j]);
					}
				}
				//==TO MAKE SPY'S APPEAR DAMAGED ON LOW HEALTH==//
				if (((Spy*)Rects[i])->getHealth() < 3 && (rand() % 6 + 1) > 5)
				{
					particles->add(smoke, Point{ Rects[i]->getPosition().x + 5 - 3 + (rand() % 6 + 1), Rects[i]->getPosition().y + 5 - 3 + (rand() % 6 + 1) });
					if ((rand() % 6 + 1) > 5)
					{
						particles->add(spark, Rects[i]->getPosition(), -2 + (rand() % 4 + 1), -2 + (rand() % 4 + 1));
					}
				}
				if (((Spy*)Rects[i])->getHealth() <= 0)
				{

					Rects.erase(Rects.begin() + i);
				}
			}
			if (Rects[i]->getType() == grenade)
			{
				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getType() == drone && j != i)
					{
						CollisionDetection::correctPosition(Rects[i], Rects[j]);
					}
				}
			}
		}
		if (playerIndex != -1)
		{
			if (((Player*)Rects[playerIndex])->getHealth() == 0)
			{
				gfx->setScreenShakeIntensity(1.2);
				for (int l = 0; l < 40; l++)
				{
					particles->add(spark, Rects[playerIndex]->getPosition(), -5 + (rand() % 10 + 1), -10 + (rand() % 20 + 1));
				}
				for (int l = 0; l < 15; l++)
				{
					particles->add(smoke, Point{ Rects[playerIndex]->getPosition().x - 35 + (rand() % 70 + 1), Rects[playerIndex]->getPosition().y - 35 + (rand() % 70 + 1) });
				}
				Rects.erase(Rects.begin() + playerIndex);
				playerIndex = -1;
			}
		}
		particles->manage();
		projectiles->manage();
		if (playerIndex != -1)
		{
			projectiles->manageTracking(Rects[playerIndex]->getPosition());
		}
		for (int i = 0; i < Rects.size(); i++)
		{
			if (Rects[i]->getType() == drone)
			{
				if (((Drone*)Rects[i])->getFiring() && playerIndex != -1)
				{
					if (((Drone*)Rects[i])->getDroneType() == hunterDrone)
					{
						if (((Drone*)Rects[i])->getFireSide() == eleft)
						{
							projectiles->add(Point{ Rects[i]->getPosition().x, Rects[i]->getPosition().y + Rects[i]->getHeight() / 2 }, Point{ Rects[playerIndex]->getPosition().x + Rects[playerIndex]->getWidth() / 2, Rects[playerIndex]->getPosition().y + Rects[playerIndex]->getHeight() / 2 }, 18, ((Drone*)Rects[i])->getLaserColour());
						}
						else
						{
							projectiles->add(Point{ Rects[i]->getPosition().x + Rects[i]->getWidth(), Rects[i]->getPosition().y + Rects[i]->getHeight() / 2 }, Point{ Rects[playerIndex]->getPosition().x + Rects[playerIndex]->getWidth() / 2, Rects[playerIndex]->getPosition().y + Rects[playerIndex]->getHeight() / 2 }, 18, ((Drone*)Rects[i])->getLaserColour());
						}
					}
					else
					{
						projectiles->add(Point{ Rects[i]->getPosition().x + Rects[i]->getWidth() / 2, Rects[i]->getPosition().y + Rects[i]->getHeight() / 2 }, Point{ Rects[playerIndex]->getPosition().x + Rects[playerIndex]->getWidth() / 2, Rects[playerIndex]->getPosition().y + Rects[playerIndex]->getHeight() / 2 }, 18, ((Drone*)Rects[i])->getLaserColour());
					}
				}
			}
		}
		for (int i = 0; i < exitPoints.size(); i++)
		{
			exitPoints[i]->runTimer();
		}
	}
	//LevelEditor.update();////
}
void playableLevel::Render()//draws everything in the level
{
	backGround->Draw(0, camera->getPosition().x - screenWidth / 2, camera->getPosition().y - screenHeight / 2);
	gfx->ClearScreen(0.0f, 0.0f, 0.1f);
	for (int i = 0; i < Rects.size(); i++)
	{
		Rects[i]->draw();
		if (Rects[i]->getType() == player)
		{
			if (((Player*)Rects[i])->weapons.size()>0)
			{
				((Player*)Rects[i])->weapons[((Player*)Rects[i])->getWeaponInUse()]->drawOnParent(Rects[i]->getPosition(), Rects[i]->getWeaponOffsetX(), Rects[i]->getWeaponOffsetY());
			}
		}
	}
	particles->draw();
	//for debugging
	gfx->DrawRect(mousePos, 2, 2, 1, 1, 1, 1);

	if (paused)
	{
		for (int i = 0; i < Buttons.size(); i++)
		{
			Buttons[i]->draw();
		}
	}
	projectiles->draw();
	//LevelEditor.draw();////
}
void playableLevel::addPlatformFromXML(XMLElement* _parsedxml)
{
	Rects.push_back(new Platform(Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("y"))->GetText()) }, atof((char*)(const char*)(_parsedxml->FirstChildElement("width"))->GetText()), atof((char*)(const char*)(_parsedxml->FirstChildElement("height"))->GetText()), 0, 0, gfx));
}
void playableLevel::addDroneFromXML(XMLElement* _parsedxml)
{
	if (strcmp((_parsedxml->FirstChildElement("willPatrol"))->GetText(), "false") == 0)
	{
		if (strcmp((_parsedxml->FirstChildElement("type"))->GetText(), "hunter") == 0)
		{
			Rects.push_back(new Hunter(Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("y"))->GetText()) }, 10, 10, 0, 0, gfx));
		}
		else
		{
			Rects.push_back(new Spy(Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("y"))->GetText()) }, 10, 10, 0, 0, gfx));
		}
	}
	else
	{
		if (strcmp((_parsedxml->FirstChildElement("type"))->GetText(), "hunter")==0)
		{
			Rects.push_back(new Hunter(Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("y"))->GetText()) }, 10, 10, 0, 0, Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P1x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P1y"))->GetText()) }, Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P2x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P2y"))->GetText()) }, gfx));
		}
		else
		{
			Rects.push_back(new Spy(Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("y"))->GetText()) }, 10, 10, 0, 0, Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P1x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P1y"))->GetText()) }, Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P2x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("P2y"))->GetText()) }, gfx));
		}
	}
}
void playableLevel::addAllPlatformsFromXML()
{
	doc.LoadFile(xmlPath);
	XMLElement* numberOfPlatforms = doc.FirstChildElement("NUMBEROFPLATFORMS");
	for (int i = 1; i < atof((char*)(const char*)(numberOfPlatforms)->GetText()) + 1; i++)
	{
		char integer_string[4];
		sprintf_s(integer_string, "%d", i);
		char p[6] = "P";
		strcat_s(p, integer_string);
		XMLElement* parsedxml = doc.FirstChildElement(p);
		addPlatformFromXML(parsedxml);
	}
}
void playableLevel::addAllDronesFromXML()
{
	doc.LoadFile(xmlPath);
	XMLElement* numberOfDrones = doc.FirstChildElement("NUMBEROFDRONES");
	for (int i = 1; i < atof((char*)(const char*)(numberOfDrones)->GetText()) + 1; i++)
	{
		const char* sadjkn = (const char*)(numberOfDrones)->GetText();
		char integer_string[4];
		sprintf_s(integer_string, "%d", i);
		char d[6] = "D";
		strcat_s(d, integer_string);
		XMLElement* parsedxml = doc.FirstChildElement(d);
		addDroneFromXML(parsedxml);
	}
}


void playableLevel::addExitPointFromXML(XMLElement* _parsedxml)
{
	exitPoints.push_back(new exitPoint(Point{ (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("x"))->GetText()), (float)atof((char*)(const char*)(_parsedxml->FirstChildElement("y"))->GetText()) }, atof((char*)(const char*)(_parsedxml->FirstChildElement("width"))->GetText()), atof((char*)(const char*)(_parsedxml->FirstChildElement("height"))->GetText()), atof((char*)(const char*)(_parsedxml->FirstChildElement("timer"))->GetText()), atof((char*)(const char*)(_parsedxml->FirstChildElement("forcedxvel"))->GetText()), atof((char*)(const char*)(_parsedxml->FirstChildElement("level"))->GetText())));
}
Point playableLevel::getPlayerPositionFromXML()
{
	doc.LoadFile(xmlPath);
	return Point{ (float)atof((char*)(const char*)(doc.FirstChildElement("PLAYERPOS")->FirstChildElement("x"))->GetText()), (float)atof((char*)(const char*)(doc.FirstChildElement("PLAYERPOS")->FirstChildElement("y"))->GetText()) };
}
