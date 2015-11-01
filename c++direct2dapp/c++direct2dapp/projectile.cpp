#include "projectile.h"

projectile::projectile(Point _position, float _xVel, float _yVel, Graphics* _gfx)
{
	position = _position;
	lastPosition1 = _position;
	lastPosition2 = _position;
	xVel = _xVel;
	yVel = _yVel;
	gfx = _gfx;
	angle = -1.5;
}
projectile::projectile(Point _position, float _xVel, float _yVel, colour _c, Graphics* _gfx)
{
	position = _position;
	lastPosition1 = _position;
	lastPosition2 = _position;
	xVel = _xVel;
	yVel = _yVel;
	gfx = _gfx;
	angle = -1.5;
	cr = 1;
	cg = 0.1;
	cb = 0.1;
	switch (_c)
	{
	case red:
		cr = 1;
		cg = 0.2;
		cb = 0.2;
		break;
	case orange:
		cr = 1;
		cg = 0.5;
		cb = 0;
	case blue:
		cr = 0.25;
		cg = 0.66;
		cb = 1;
		break;
	}
}
projectile::projectile() {}
projectile::~projectile() {}

Point projectile::getPosition()
{
	return position;
}
void projectile::calcNewPos()
{
	lastPosition2 = lastPosition1;
	lastPosition1 = position;

	position.x += xVel;
	position.y += yVel;
}
void projectile::draw()
{
	gfx->DrawLine(position, lastPosition1, cr, cg, cb, 1);
	gfx->DrawLine(lastPosition1, lastPosition2, cr, cg, cb, 1);
}
float projectile::getxVel()
{
	return xVel;
}
float projectile::getyVel()
{
	return yVel;
}
Point projectile::getLastPosition()
{
	return lastPosition1;
}
void projectile::setxVel(float _xVel) {
	xVel = _xVel;
}
void projectile::setyVel(float yv) {
	yVel = yv;
}
float projectile::getSpeed()
{
	return speed;
}
float projectile::getAngle()
{
	return angle;
}