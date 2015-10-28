#include "Spy.h"
#include "stdio.h"
#include <math.h>
#include "CollisionDetection.h"

Spy::Spy() {}

Spy::Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi) :
	Rect(_position, _width, _height, _yVel, _xVel, false, spy, false, gfxi)
{
	mode = inactive;
}
Spy::Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Point _p1, Point _p2, Graphics * gfxi) :
	Rect(_position, _width, _height, _yVel, _xVel, false, spy, false, gfxi)
{
	patrolDestinations.push_back(_p1);
	patrolDestinations.push_back(_p2);
	mode = patrol;
}

Spy::~Spy()
{
	delete up;
	delete down;
	delete left;
	delete right;
}

void Spy::draw()
{
	if (health > 0)
	{
		if (yVel < 0)
		{
			up->Draw(0, position.x, position.y);
		}
		if (yVel >= 0)
		{
			down->Draw(0, position.x, position.y);
		}
		if (xVel < 0)
		{
			left->Draw(0, position.x, position.y);
		}
		if (xVel > 0)
		{
			right->Draw(0, position.x - 8, position.y);
		}
	}
	/*
	for (int i = trail.size()-2; i > 0; i--)
	{
		gfx->DrawLine(trail[i+1], trail[i], 1, 1, 1, 1);
	}
	for (int i = trail1.size() - 2; i > 0; i--)
	{
		gfx->DrawLine(trail1[i + 1], trail1[i], 1, 1, 1, 1);
	}
	for (int i = trail2.size() - 2; i > 0; i--)
	{
		gfx->DrawLine(trail2[i + 1], trail2[i], 1, 1, 1, 1);
	}
	*/
	//gfx->DrawRect(destinations[0], 2, 2, 1, 0, 0, 1);
	firing = false;
	firecooldown--;
}

void Spy::calcNewPos(Point _position)
{
	position.x += width / 2;
	position.y += height / 2;
	behaviorType result = follow;
	for (int j = 0; j < Rects.size(); j++)
	{
		if (Rects[j]->getType() == platform && CollisionDetection::checkRectLineIntersect(Rects[j]->getPosition(), Rects[j]->getWidth(), Rects[j]->getHeight(), position, _position))
		{
			result = hover;
			if (mode == inactive)
			{
				result = inactive;
			}
			if (mode == patrol)
			{
				result = patrol;
			}
			break;
		}

	}
	mode = result;

	float theta = atan(-1 * (_position.y - position.y) / (_position.x - position.x));

	switch (mode)
	{
	case patrol:
		if (CollisionDetection::checkPointRectIntersect(patrolDestinations[nextPatrolIndex], Point{ position.x - (width / 2) - 0.5f, position.y - (height / 2) - 0.5f }, width + 1, height + 1))
		{
			if (nextPatrolIndex == 0)
			{
				nextPatrolIndex++;
			}
			else
			{
				nextPatrolIndex--;
			}
		}
		if (patrolDestinations[nextPatrolIndex].y == position.y)
		{
			if (patrolDestinations[nextPatrolIndex].x > position.x)
			{
				xVel = speed;
				yVel = 0;
			}
			else
			{
				xVel = -speed;
				yVel = 0;
			}
		}
		else if (patrolDestinations[nextPatrolIndex].x == position.x)
		{
			if (patrolDestinations[nextPatrolIndex].y > position.y)
			{
				yVel = speed;
				xVel = 0;
			}
			else
			{
				yVel = -speed;
				xVel = 0;
			}
		}
		else
		{


			theta = atan(-1 * (patrolDestinations[nextPatrolIndex].y - position.y) / (patrolDestinations[nextPatrolIndex].x - position.x));
			if (patrolDestinations[nextPatrolIndex].x > position.x) {
				yVel = sin(theta) * -1 * speed;
				xVel = cos(theta) * speed;
			}
			else {
				yVel = sin(theta) * speed;
				float lol = sin(theta);
				xVel = cos(theta) * -1 * speed;
			}
		}
	case inactive:
		lastBehavior = inactive;
		break;
	case follow:
		if (_position.x > position.x) {
			yVel = sin(theta) * -1 * speed;
			xVel = cos(theta) * speed;
		}
		else {
			yVel = sin(theta) * speed;
			xVel = cos(theta) * -1 * speed;
		}
		destinations.clear();
		destinations.push_back(_position);
		lastBehavior = follow;
		if (firecooldown < 0)
		{
			firecooldown = 120;
			firing = true;
		}
		break;
	case hover:
		int testx = destinations[0].x;
		int testy = destinations[0].y;
		if (destinations.size() > 0 && CollisionDetection::checkPointRectIntersect(destinations[0], Point{ position.x - (width / 2) - 0.5f, position.y - (height / 2) - 0.5f } , width+1, height+1))
		{
			destinations.erase(destinations.begin());
		}
		if (destinations.size() > 0)
		{
			for (int i = 0; i < Rects.size(); i++)
			{
				if (Rects[i]->getType() == platform)
				{
					if (CollisionDetection::checkRectLineIntersect(Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight(), Point{ position.x, position.y }, destinations[0]))
					{
						destinations[0] = CollisionDetection::getClosestTarget(position, destinations[0]);
					}
				}
			}
			if (destinations[0].y == position.y)
			{
				if (destinations[0].x > position.x)
				{
					xVel = speed;
					yVel = 0;
				}
				else
				{
					xVel = -speed;
					yVel = 0;
				}
			}
			else if (destinations[0].x == position.x)
			{
				if (destinations[0].y > position.y)
				{
					yVel = speed;
					xVel = 0;
				}
				else
				{
					yVel = -speed;
					xVel = 0;
				}
			}
			else
			{


				theta = atan(-1 * (destinations[0].y - position.y) / (destinations[0].x - position.x));
				if (destinations[0].x > position.x) {
					yVel = sin(theta) * -1 * speed;
					xVel = cos(theta) * speed;
				}
				else {
					yVel = sin(theta) * speed;
					float lol = sin(theta);
					xVel = cos(theta) * -1 * speed;
				}
			}
		}
		else
		{
			destinations.push_back(Point{ position.x, position.y-50 });
			destinations.push_back(Point{ position.x, position.y });
			destinations.push_back(Point{ position.x, position.y+50 });
			destinations.push_back(Point{ position.x, position.y });
			destinations.push_back(Point{ position.x+50, position.y });
			destinations.push_back(Point{ position.x, position.y });
			destinations.push_back(Point{ position.x, position.y - 50 });
			destinations.push_back(Point{ position.x, position.y });
		}
		if (hoverVel > 0.8)
		{
			hovermode = rise;
		}
		else if (hoverVel < -0.8)
		{
			hovermode = fall;
		}
		if (hovermode == rise)
		{
			hoverVel-=0.05;
		}
		else if (hovermode == fall)
		{
			hoverVel += 0.05;
		}
		lastBehavior = hover;
		yVel += hoverVel;
		break;
	}
	position.x -= width / 2;
	position.y -= height / 2;
	/*
	trail.push_back(position);
	trail1.push_back(position);
	trail2.push_back(position);
	if (trail.size() == 30)
	{
		trail.erase(trail.begin() + 0);
	}
	if (trail1.size() == 20)
	{
		trail1.erase(trail1.begin() + 0);
	}
	if (trail2.size() == 25)
	{
		trail2.erase(trail2.begin() + 0);
	}
	for (int i = trail1.size() - 2; i > 0; i--)
	{
		trail1[i].y++;
	}
	for (int i = trail2.size() - 2; i > 0; i--)
	{
		trail2[i].y--;
	}*/
}

void Spy::load()
{
	left = new SpriteSheet(L"spy_left.png", 16, 8, 0, 1, gfx);
	right = new SpriteSheet(L"spy_right.png", 16, 8, 0, 1, gfx);
	up = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
	down = new SpriteSheet(L"spy_down.png", 8, 16, 0, 1, gfx);
	normal = new SpriteSheet(L"spy_up.png", 8, 16, 0, 1, gfx);
	health = 4;
	speed = 1.5;
	hovermode = rise;

	roamTimer = 0;
	destinations.push_back(Point{ position.x, position.y});
	nextPatrolIndex = 0;
}
void Spy::subtractHealth(int _amount)
{
	health -= _amount;
}
int Spy::getHealth()
{
	return health;
}
void Spy::setMode(behaviorType _mode)
{
	mode = _mode;
}
bool Spy::getFiring()
{
	return firing;
}