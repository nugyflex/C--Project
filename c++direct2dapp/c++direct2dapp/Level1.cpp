#include "Level1.h"
#include <stdio.h>
#include <math.h>
void Level1::Load()
{

	particles = new particleCollection(gfx);
	soundLatch = 0;
	testvar = 0;
	fc = 0;
	Button* temp = new MenuButton(0, 0, gfx);
	buttons.push_back(temp);
	temp = new ExitButton(0, 100, gfx);
	buttons.push_back(temp);


	camera = new Camera(Point{ 0,0 });
	backGround  = new SpriteSheet(L"newbackground.png", 1280, 720, 0, 0, gfx);

	Rect* tempobject = new Player(Point{ 640,9 }, 12, 54, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 50, 298 }, 1200, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 50, 500 }, 1600, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Platform(Point{ 500, 450 }, 50, 50, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new FireBall(Point{ 200, 200 }, 0, 0, gfx);
	Rects.push_back(tempobject);
	tempobject = new Spy(Point{ 200, 200 }, 10, 10, 0, 0, gfx);
	Rects.push_back(tempobject);
	Rects[0]->load();
	Rects[4]->load();
	Rects[5]->load();
	Gun* newgun = new Gun(300, 300, gfx);
	weapons.push_back(newgun);
	weapons[0]->load();
	weapons[0]->setParent(true);
	((Player*)Rects[0])->addWeapon(weapons[0]);
	//particles->add(spark, Point{ 0,0 });

}

void Level1::Unload() {
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

void Level1::Update()
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
		//makes the mouse movie with the camera
		gameController::mouse.x += camera->getxVel();
		gameController::mouse.y += camera->getyVel();
		camera->calcNewPos(Rects[0]->getPosition());
		cameraPos = camera->getPosition();

		if (gameController::mouseLeft)
		{
			for (int i = 0; i < Rects.size(); i++)
			{
				if (Rects[i]->getType() == player)
				{
					if (((Player*)Rects[i])->weapons.size()>0)
					{
						Point temppoint = CollisionDetection::getClosestTarget(((Player*)Rects[0])->getWeaponPos(), CollisionDetection::projectLineToEdge(cameraPos, 1280, 720, ((Player*)Rects[0])->getWeaponPos(), mousePos));
						if (((Player*)Rects[i])->weapons[((Player*)Rects[i])->getWeaponInUse()]->getCooldown() <-2)
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
						if (((Player*)Rects[i])->weapons[((Player*)Rects[i])->getWeaponInUse()]->fire())
						{


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
									particles->add(smoke, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) }, 0, 0);
									if (rand() % 10 + 1 > 6)
									{
										particles->add(spark, Point{ temppoint.x - 2.5f - 3 + (rand() % 6 + 1), temppoint.y - 2.5f - 3 + (rand() % 6 + 1) }, -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);

									}
								}
								for (int j = 0; j < Rects.size(); j++)
								{
									if (Rects[j]->getType() == spy)
									{
										if (CollisionDetection::checkRectLineIntersect(Rects[j]->getPosition(), Rects[j]->getWidth(), Rects[j]->getHeight(), ((Player*)Rects[0])->getWeaponPos(), temppoint))
										{
											((Spy*)Rects[j])->subtractHealth(1);
											if (((Spy*)Rects[j])->getHealth() < 1)
											{
												for (int l = 0; l < 30; l++)
												{
													particles->add(spark, Rects[j]->getPosition(), -2 + (rand() % 40 + 1) / 10, -4 + (rand() % 80 + 1) / 10);

												}
												Rects.erase(Rects.begin() + j);
												gfx->setScreenShakeIntensity(0.5);
												//commented until i add offsets to spawning smoke particles
												/*
												for (int l = 0; l < 20; l++)
												{
													particles->add(smoke, Rects[j]->getWeaponPos(), 0, 0);

												}*/
											}
										}
									}
								}
								
						}
					}
				}
			}
		}

		//VARIABLE JUMP
		if (gameController::keyW)
		{
			if (Rects[0]->getyVel() >= 0)
			{
				for (int j = 0; j < Rects.size(); j++)
				{
					if (Rects[j]->getFixed() && CollisionDetection::getSide(Rects[0], Rects[j]) == 4)
					{
						Rects[0]->setyVel(-8);
					}
				}
			}
		}
		else
		{
			if (Rects[0]->getyVel() < -3)
			{
				Rects[0]->setyVel(-3);
			}
		}
		if (gameController::keyA)
		{


			Rects[0]->setxVel(-3);


		}
		if (!gameController::keyA && !gameController::keyD)
		{
			Rects[0]->setxVel(0);
		}

		if (gameController::keyD)
		{

			Rects[0]->setxVel(3);

		}
		if (gameController::keyA && gameController::keyD)
		{
			Rects[0]->setxVel(0);
		}
		for (int i = 0; i < Rects.size(); i++)
		{
			//Gravity
			if (Rects[i]->getGravity())
			{
				Rects[i]->setyVel(Rects[i]->getyVel() + 0.51f);
			}
			//adding xvel x to x and yvel to y
			Rects[i]->calcNewPos();
			if (Rects[i]->getType() == spy)
			{
				Rects[i]->calcNewPos(Rects[0]->getPosition());
			}

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

		}

		for (int i = 0; i < Rects.size(); i++)
		{
			//deleting fireballs
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
		particles->manage();
		/*// waterfall of spark particles
		float random = rand();
		float randmax = RAND_MAX;
		float test = floor((random / randmax) * 100);
		particles->add(spark, Point{ test, 0 }, 0);*/

	}
}
void Level1::Render()
{
	backGround->Draw(0, camera->getPosition().x - 640, camera->getPosition().y - 360);
		//gfx->ClearScreen(0.0f, 0.0f, 0.0f);

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
		if (paused)
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				buttons[i]->draw();
			}
		}
		particles->draw();
}