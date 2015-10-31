#pragma once
#pragma once
#include "rectangle.h"
#include "SpriteSheet.h"

enum behaviorType { hover, follow, inactive, patrol };
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
	behaviorType lastBehavior;
	hoverMode hovermode;
	int roamTimer;
	float baseyVel;
	vector<Point> destinations;
	vector<Point> patrolDestinations;
	int nextPatrolIndex;
	/*vector<Point> trail;
	vector<Point> trail1;
	vector<Point> trail2;*/
	float hoverVel;
	bool firing;
	int shootCooldown;
	int maxShootCooldown;
public:
	Spy();
	Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	Spy(Point _position, float _width, float _height, float _yVel, float _xVel, Point _p1, Point _p2, Graphics * gfxi);
	~Spy();
	void load() override;
	void draw() override;
	void calcNewPos(Point _position) override;
	void subtractHealth(int _amount);
	int getHealth();
	void setMode(behaviorType _mode);
	bool getFiring();
};