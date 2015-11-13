#pragma once
#include "rectangle.h"
#include "SpriteSheet.h"

enum behaviorType { hover, follow, inactive, patrol };
enum hoverMode { rise, fall };
enum droneType {spyDrone, hunterDrone };
class Drone : public Rect {
protected:
	SpriteSheet* left;
	SpriteSheet* right;
	SpriteSheet* up;
	SpriteSheet* down;
	SpriteSheet* normal;
	SpriteSheet* default;
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
	float hoverVel;
	bool firing;
	int shootCooldown;
	int maxShootCooldown;
	colour laserColour;
	droneType type;
public:
	Drone();
	Drone(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi);
	Drone(Point _position, float _width, float _height, float _yVel, float _xVel, Point _p1, Point _p2, Graphics * gfxi);
	~Drone();
	virtual void load() override;
	virtual void draw() override;
	void calcNewPos(Point _position) override;
	void subtractHealth(int _amount);
	int getHealth();
	void setMode(behaviorType _mode);
	bool getFiring();
	colour getLaserColour();
	droneType getDroneType();
};