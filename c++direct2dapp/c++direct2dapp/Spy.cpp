#include "Spy.h"
#include "stdio.h"
#include <math.h>
#include "CollisionDetection.h"

Spy::Spy() {}

Spy::Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi) :
	Rect(_position, _width, _height, _yVel, _xVel, false, spy, false, gfxi)
{

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
			break;
		}

	}
	mode = result;

	float theta = atan(-1 * (_position.y - position.y) / (_position.x - position.x));

	switch (mode)
	{
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
		break;
	case hover:
		float testx = destinations[0].x;
		float testy = destinations[0].y;
		if (destinations.size() > 0 && CollisionDetection::checkPointRectIntersect(destinations[0], Point{ position.x - width / 2, position.y - height / 2 }, width, height))
		{
			destinations.erase(destinations.begin());
		}
		if (destinations.size() > 0)
		{
			for (int i = 0; i < Rects.size(); i++)
			{
				if (Rects[i]->getType() == platform)
				{
					if (CollisionDetection::checkRectLineIntersect(Rects[i]->getPosition(), Rects[i]->getWidth(), Rects[i]->getHeight(), position, destinations[0]))
					{
						destinations[0] = CollisionDetection::getClosestTarget(position, destinations[0]);
					}
				}
			}
			float testx = destinations[0].x;
			float testy = destinations[0].y;
			theta = atan(-1 * (destinations[0].y - position.y) / (destinations[0].x - position.x));
			if (destinations[0].x > position.x) {
				yVel = sin(theta) * -1 * speed;
				xVel = cos(theta) * speed;
			}
			else {
				float testx = destinations[0].x;
				float testy = destinations[0].y;
				yVel = sin(theta) * speed;
				xVel = cos(theta) * -1 * speed;
			}
		}
		else
		{
			destinations.push_back(Point{ position.x+50, position.y });
			destinations.push_back(Point{ position.x-50, position.y });
			destinations.push_back(Point{ position.x, position.y+50 });
			destinations.push_back(Point{ position.x, position.y-50 });
			destinations.push_back(Point{ position.x+1, position.y+1 });
		}
		lastBehavior = hover;
		break;
	}
	position.x -= width / 2;
	position.y -= height / 2;
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
	mode = inactive;
	roamTimer = 0;
	destinations.push_back(Point{ position.x, position.y});
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