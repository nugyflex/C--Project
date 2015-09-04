#include "Rectangle.h"

Rect::Rect(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics * gfxi)
{
	position = _position;
	width = _width;
	height = _height;
	yVel = _yVel;
	xVel = _xVel;
	gfx = gfxi;
#pragma once
}


Rect::~Rect()
{
}

int Rect::getWidth(){

	return width;
}

int Rect::getHeight(){

	return height;
}

float Rect::getyVel(){

	return yVel;
}
Point Rect::getPosition(){

	return position;
}
float Rect::getY(){

	return position.y;
}

void Rect::changeY(float _yChange)
{
	position.y += _yChange;
}

void Rect::setWidth(int _width){
	width = _width;
}

void Rect::setHeight(int _height){
	height = _height;
}

void Rect::setyVel(float yv){
	yVel = yv;
}

void Rect::setY(float ys){
	position.y = ys;
}

float Rect::getxVel(){

	return xVel;
}
float Rect::getX(){

	return position.x;
}

void Rect::changeX(float _xChange)
{
	position.x += _xChange;
}

void Rect::setxVel(float _xVel){
	xVel = _xVel;
}

void Rect::setX(float _x){
	position.x = _x;
}
void Rect::calcNewPos(){
	setX(getX() + getxVel());
	setY(getY() + getyVel());
}

void Rect::draw()
{

	gfx->FillRect(position, width, height, 1.0f, 1.0f, 1.0f, 1.0f);

}

