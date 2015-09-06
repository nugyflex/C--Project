#include "Camera.h"
#include <math.h>

Camera::Camera(Point _position)
{
	position = _position;
	yVel = 0;
	xVel = 0;
#pragma once
}
Camera::~Camera()
{
}
float Camera::getyVel(){

	return yVel;
}
Point Camera::getPosition(){

	return position;
}
float Camera::getY(){

	return position.y;
}
void Camera::setyVel(float yv){
	yVel = yv;
}
void Camera::setY(float ys){
	position.y = ys;
}
float Camera::getxVel(){

	return xVel;
}
float Camera::getX(){

	return position.x;
}
void Camera::setxVel(float _xVel){
	xVel = _xVel;
}
void Camera::setX(float _x){
	position.x = _x;
}
void Camera::calcNewPos(Point _position){
	if (position.x < _position.x) {
		setxVel(floor((_position.x - position.x) / 25));
	}
	if (position.x > _position.x) {
		setxVel(floor((position.x - _position.x) / -25));
	}
	if (position.y < _position.y) {
		setyVel(floor(((_position.y - 10) - position.y) / 15));
	}
	if (position.y > _position.y) {
		setyVel(floor((position.y - (_position.y - 10)) / -15));
	}
	setX(getX() + getxVel());
	setY(getY() + getyVel());
}