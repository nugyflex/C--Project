#pragma once
#include "Graphics.h"
#include <string.h>
#include <vector>

using namespace std;

enum rectType { platform, player, fireball, drone, grenade }; //this is an enum, very useful!

class Rect //the Rect class, inherited by fireball, spy, player, and platform
{
protected:
	Point position;
	float width;
	float height;
	float yVel;
	float xVel;
	bool fixed;
	bool gravity;
	rectType type;
	Graphics *gfx;

public:
	Rect();
	Rect(Point _position, float _width, float _height, float _yVel, float _xVel, bool _fixed, rectType _type, bool gravity, Graphics * gfxi);
	~Rect();

	float getWidth();
	float getHeight();
	float getY();
	float getX();
	Point getPosition();
	void changeY(float _yChange);
	void changeX(float _xChange);
	float getyVel();
	float getxVel();
	void setyVel(float _yVel);
	void setxVel(float _xVel);
	void setPosition(Point _position);
	void setX(float _x);
	void setY(float _y);
	void setWidth(float _width);
	void setHeight(float _height);
	bool getFixed();
	virtual void calcNewPos();
	virtual void calcNewPos(Point _p);
	void ggravity(float _g);
	rectType getType();
	bool getGravity();

	virtual void draw();

	virtual void load();
	virtual int getWeaponOffsetX();
	virtual int getWeaponOffsetY();
};
extern vector<Rect*> Rects;