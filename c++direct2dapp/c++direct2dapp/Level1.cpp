#include "Level1.h"
#include <stdio.h>
#include <math.h>

void Level1::Load() //loads the level, called when the level is instantiated
{
	projectiles = new projectileCollection(gfx);
	particles = new particleCollection(gfx);
	soundLatch = 0;
	testvar = 0;
	fc = 0;
	Button* temp = new MenuButton(0, 0, gfx);
	buttons.push_back(temp);
	temp = new ExitButton(0, 100, gfx);
	buttons.push_back(temp);


	camera = new Camera(Point{ 0,0 });
	backGround  = new SpriteSheet(L"sanddunes.png", screenWidth, screenHeight, 0, 0, gfx);

	Rect* tempobject = new Player(Point{ 750, 240 }, 12, 54, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 50, 300 }, 1200, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 1300, 300 }, 75, 25, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 50, 500 }, 1600, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 550, 200 }, 50, 100, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 500, 250 }, 50, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 600, 250 }, 50, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 500, 450 }, 50, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 1300, 450 }, 50, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 1350, 400 }, 50, 100, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 1400, 350 }, 50, 150, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 1450, 300 }, 50, 200, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 1500, 0 }, 50, 500, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 0, 0 }, 50, 550, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new FireBall(Point{ 200, 200 }, 0, 0, gfx);
	Rects.push_back(tempobject);
	//for (int i = 0; i < 2; i++)
	//{
		//tempobject = new Spy(Point{ 200, 200 }, 10, 10, 0, 0, gfx);
		//Rects.push_back(tempobject);
	Rects.push_back(new Spy(Point{ 220, 220 }, 10, 10, 0, 0, Point{ 100, 220 }, Point{ 400, 220 }, gfx));
	Rects.push_back(new Spy(Point{ 220, 400 }, 10, 10, 0, 0, Point{ 100, 400 }, Point{ 800, 400 }, gfx));
	//}
	for (int i = 0; i < Rects.size(); i++)
	{
		Rects[i]->load();
	}
	projectiles->add(Point{ 300, 100 }, 6, 3);
	Gun* newgun = new Gun(300, 300, gfx);
	weapons.push_back(newgun);
	weapons[0]->load();
	weapons[0]->setParent(true);
	((Player*)Rects[0])->addWeapon(weapons[0]);
	//particles->add(spark, Point{ 0,0 });
	
	saveFileOut.open("save.txt");
	saveFileIn.open("save.txt");
	float x, y;
	saveFileIn >> x >> y;

}

void Level1::Unload() { //called when the level is finishded
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

void Level1::Update() //updates all physics, controls and collision detection (and more!)
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
			Rects.push_back(new Player(Point{ 750, 240 }, 12, 54, 0, 0, gfx));
			Rects[playerIndex]->load();
		}
		//makes the mouse movie with the camera
		gameController::mouse.x += camera->getxVel();
		gameController::mouse.y += camera->getyVel();
		if (playerIndex != -1)
		{
			camera->calcNewPos(Rects[playerIndex]->getPosition());
		}
		cameraPos = camera->getPosition();

		if (gameController::mouseLeft)
		{
				if (playerIndex != -1)
				{
					if (((Player*)Rects[playerIndex])->weapons.size()>0)
					{
						Point temppoint = CollisionDetection::getClosestTarget(((Player*)Rects[playerIndex])->getWeaponPos(), CollisionDetection::projectLineToEdge(cameraPos, ((Player*)Rects[playerIndex])->getWeaponPos(), mousePos));
						if (((Player*)Rects[playerIndex])->weapons[((Player*)Rects[playerIndex])->getWeaponInUse()]->getCooldown() <-2)
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
									if (Rects[j]->getType() == spy)
									{
										if (CollisionDetection::checkRectLineIntersect(Rects[j]->getPosition(), Rects[j]->getWidth(), Rects[j]->getHeight(), ((Player*)Rects[playerIndex])->getWeaponPos(), temppoint))
										{
											((Spy*)Rects[j])->subtractHealth(1);
											if (((Spy*)Rects[j])->getHealth() < 1)
											{
												temppoint = Rects[j]->getPosition();
												Rects.push_back(new Spy(Point{ 220, 220 }, 10, 10, 0, 0, Point{ 100, 220 }, Point{ 400, 220 }, gfx));
												Rects.erase(Rects.begin() + j);

												Rects[Rects.size() - 1]->load();
												gfx->setScreenShakeIntensity(0.25);
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
									}
								}
						}
					}
				}

		}
		//CONTROLS
		//VARIABLE JUMP
		if (playerIndex != -1)
		{
			if (gameController::keyW)
			{
				//saveFileOut << Rects[0]->getX() << endl;
				//saveFileOut << Rects[0]->getY() << endl;
				if (Rects[playerIndex]->getyVel() >= 0)
				{
					for (int j = 0; j < Rects.size(); j++)
					{
						if (Rects[j]->getFixed() && CollisionDetection::getSide(Rects[playerIndex], Rects[j]) == 4)
						{
							Rects[playerIndex]->setyVel(-8);
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
		}
		for (int i = 0; i < Rects.size(); i++)
		{
			//Gravity
			if (Rects[i]->getGravity())
			{
				Rects[i]->setyVel(Rects[i]->getyVel() + 0.51f);
			}
			//adding xvel x to x and yvel to y
			if (Rects[i]->getType() == spy && playerIndex != -1)
			{
				Rects[i]->calcNewPos(Rects[playerIndex]->getPosition());
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
			if (Rects[i]->getType() == spy)
			{
				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getType() == spy && j != i)
					{
						CollisionDetection::correctPosition(Rects[i], Rects[j]);
					}
				}
				if (((Spy*)Rects[i])->getHealth() < 3 && (rand() % 6 + 1) > 5)
				{
					particles->add(smoke, Point{ Rects[i]->getPosition().x + 5 - 3 + (rand() % 6 + 1), Rects[i]->getPosition().y + 5 - 3 + (rand() % 6 + 1) });
					if ((rand() % 6 + 1) > 5)
					{
						particles->add(spark, Rects[i]->getPosition(), -2 + (rand() % 4 + 1), -2 + (rand() % 4 + 1));
					}
				}
			}
			if (Rects[i]->getType() == fireball)
			{

				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getType() == platform)
					{
						if (CollisionDetection::CheckRectangleIntersect(Rects[i], Rects[j]))
						{
							Rects.erase(Rects.begin() + i);
							i--;
							break;
						}
					}

				}

			}
		}
		if (playerIndex != -1)
		{
			if (((Player*)Rects[playerIndex])->getHealth() == 0)
			{
				gfx->setScreenShakeIntensity(1);
				for (int l = 0; l < 20; l++)
				{
					particles->add(spark, Rects[playerIndex]->getPosition(), -5 + (rand() % 10 + 1), -10 + (rand() % 20 + 1));
				}
				for (int l = 0; l < 25; l++)
				{
					particles->add(smoke, Point{ Rects[playerIndex]->getPosition().x - 35 + (rand() % 70 + 1), Rects[playerIndex]->getPosition().y - 35 + (rand() % 70 + 1) });

				}
				Rects.erase(Rects.begin() + playerIndex);
			}
		}

		particles->manage();
		projectiles->manage();
		for (int i = 0; i < Rects.size(); i++)
		{
			if (Rects[i]->getType() == spy)
			{
				if (((Spy*)Rects[i])->getFiring() & playerIndex != -1)
				{
					projectiles->add(Rects[i]->getPosition(), Point{ Rects[playerIndex]->getPosition().x + Rects[playerIndex]->getWidth()/2, Rects[playerIndex]->getPosition().y + Rects[playerIndex]->getHeight() / 2 }, 20);
				}
			}
		}
		/*// waterfall of spark particles
		float random = rand();
		float randmax = RAND_MAX;
		float test = floor((random / randmax) * 100);
		particles->add(spark, Point{ test, 0 }, 0);*/
	}
}
void Level1::Render()//draws everything in the level
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