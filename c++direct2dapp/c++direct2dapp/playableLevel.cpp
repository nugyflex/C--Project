#include "playableLevel.h"
#include <stdio.h>
#include <math.h>
void playableLevel::loadObjects()
{
}
void playableLevel::Load() //loads the level, called when the level is instantiated
{
	projectiles = new projectileCollection(gfx);
	particles = new particleCollection(gfx);
	Button* temp = new MenuButton(0, 0, gfx);
	buttons.push_back(temp);
	temp = new ExitButton(0, 100, gfx);
	buttons.push_back(temp);
	boundaryIn.x = -100000;
	boundaryIn.y = -100000;
	boundaryOut.x = 100000;
	boundaryOut.y = 100000;
	loadObjects();
	camera = new Camera(Point{ 0,0 });

	for (int i = 0; i < Rects.size(); i++)
	{
		Rects[i]->load();
	}
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
}

void playableLevel::Unload() { //called when the level is finishded
	delete backGround;
	delete camera;
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	for (auto it = Rects.begin(); it != Rects.end(); ++it) {
		delete *it;
	}
	Rects.clear();
	delete particles;
}

void playableLevel::Update() //updates all physics, controls and collision detection (and more!)
{
	if (paused)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			if (!lastMouseLeft && mouseLeft && CollisionDetection::checkPointRectIntersect(mousePos, Point{ buttons[i]->getPosition().x + cameraPos.x, buttons[i]->getPosition().y + cameraPos.y }, 100, 50))
			{
				buttons[i]->action();
			}
		}
	}
	else
	{
		playerIndex = -1;
		for (int i = 0; i < Rects.size(); i++)
		{
			if (Rects[i]->getType() == player)
			{
				playerIndex = i;
			}
		}
		if (playerIndex == -1 && gameController::space == true)
		{
			playerIndex = Rects.size();
			Rects.push_back(new Player(Point{ 200, 240 }, 12, 54, 0, 0, gfx));
			Rects[playerIndex]->load();
			((Player*)Rects[playerIndex])->addWeapon(weapons[0]);
		}
		//makes the mouse movie with the camera
		gameController::mouse.x += camera->getxVel();
		gameController::mouse.y += camera->getyVel();
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
				if (((Player*)Rects[playerIndex])->weapons.size() > 0)
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
		if (playerIndex != -1)
		{
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
							Rects[playerIndex]->setyVel(-8);
							Rects[playerIndex]->setxVel(Rects[playerIndex]->getyVel() + Rects[playerIndex]->getyVel() / 5);
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
			if (gameController::keyA)
			{
				Rects[playerIndex]->setxVel(-3);
			}
			if (!gameController::keyA && !gameController::keyD)
			{
				Rects[playerIndex]->setxVel(0);
			}

			if (gameController::keyD)
			{
				Rects[playerIndex]->setxVel(3);
			}
			if (gameController::keyA && gameController::keyD)
			{
				Rects[playerIndex]->setxVel(0);
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
			if (!Rects[i]->getFixed() && Rects[i]->getType() != fireball)
			{
				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getFixed())
					{
						CollisionDetection::correctPosition(Rects[i], Rects[j]);
					}
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
					projectiles->add(Point{ Rects[i]->getPosition().x + Rects[i]->getWidth() / 2, Rects[i]->getPosition().y + Rects[i]->getHeight() / 2 }, Point{ Rects[playerIndex]->getPosition().x + Rects[playerIndex]->getWidth() / 2, Rects[playerIndex]->getPosition().y + Rects[playerIndex]->getHeight() / 2 }, 18, ((Drone*)Rects[i])->getLaserColour());
				}
			}
		}
		for (int i = 0; i < exitPoints.size(); i++)
		{
			exitPoints[i]->runTimer();
		}
	}
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
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->draw();
		}
	}
	projectiles->draw();
}