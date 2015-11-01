#include "Ball.h"

Ball::Ball(Point _center, int _radius, float _yVel, float xv, Graphics * gfxi)
{
	center = _center;
	radius = _radius;
	yVel = _yVel;
	xVel = xv;
	gfx = gfxi;
}

Ball::~Ball()
{
}

int Ball::getRadius() {
	return radius;
}

float Ball::getyVel() {
	return yVel;
}
float Ball::getY() {
	return center.y;
}

void Ball::changeY(float _yChange)
{
	center.y += _yChange;
}

void Ball::setRadius(int _radius) {
	radius = _radius;
}

void Ball::setyVel(float _yVel) {
	yVel = _yVel;
}

void Ball::setY(float _y) {
	center.y = _y;
}
void Ball::setX(float _x) {
	center.x = _x;
}

float Ball::getxVel() {
	return xVel;
}
float Ball::getX() {
	return center.x;
}

void Ball::changeX(float _xChange)
{
	center.x += _xChange;
}

void Ball::setxVel(float _xVel) {
	xVel = _xVel;
}

void Ball::calcNewPos() {
	setX(getX() + getxVel());
	setY(getY() + getyVel());
}

void Ball::draw()
{
	gfx->DrawCircle(center, radius, 1.0f, 1.0f, 1.0f, 1.0f);
	gfx->DrawRect(center, 20, 100, 1.0f, 1.0f, 1.0f, 1.0f);
	Point center1 = { 300, 200 };
	gfx->DrawLine(center, center1, 1.0f, 0.5f, 0.5f, 1.0f);
	if (center.y < 300)
	{
		gfx->DrawCircle(center, radius, 1.0f, 0.2f, 0.2f, 1.0f);
	}
	if (CollisionDetection::finddistance(center.x, center.y, center1.x, center1.y) < radius)
	{
		gfx->DrawLine(center, center1, 1.0f, 0.1f, 0.1f, 1.0f);
	}
}