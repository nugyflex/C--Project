#include "projectile.h"

projectile::projectile(Point _position, float _xVel, float _yVel, Graphics* _gfx)
{
	position = _position;
	xVel = _xVel;
	yVel = _yVel;
	gfx = _gfx;
}
projectile::projectile(){}
projectile::~projectile(){}

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
	gfx->DrawLine(position, lastPosition1, 0.8, 0.4, 0.2, 1);
	gfx->DrawLine(lastPosition1, lastPosition2, 0.8, 0.4, 0.2, 1);
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