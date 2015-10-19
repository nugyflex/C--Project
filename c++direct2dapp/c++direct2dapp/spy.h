#pragma once
#pragma once
#include "rectangle.h"
#include "SpriteSheet.h"

enum behaviorType { hover, follow };
enum hoverMode { rise, fall };
class Spy : public Rect {
	SpriteSheet* left;
	SpriteSheet* right;
	SpriteSheet* up;
	SpriteSheet* down;
	SpriteSheet* normal;
	int health;
	float speed;
	behaviorType mode;
	hoverMode hovermode;
	int chaseTimer;
public:
	Spy();
	Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	~Spy();
	void load() override;
	void draw() override;
	void calcNewPos(Point _position) override;
	void subtractHealth(int _amount);
	int getHealth();
	void setMode(behaviorType _mode);
};