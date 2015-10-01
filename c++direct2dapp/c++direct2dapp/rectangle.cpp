#include "Rectangle.h"
using namespace std;

Rect::Rect(Point _position, float _width, float _height, float _yVel, float _xVel, bool _fixed, rectType _type, bool _gravity, Graphics * gfxi)
{
	position = _position;
	width = _width;
	height = _height;
	yVel = _yVel;
	xVel = _xVel;
	gfx = gfxi;
	fixed = _fixed;
	type = _type;
	gravity = _gravity;
}
Rect::Rect(){}


Rect::~Rect()
{
}

float Rect::getWidth(){

	return width;
}

float Rect::getHeight(){

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

void Rect::setWidth(float _width){
	width = _width;
}

void Rect::setHeight(float _height){
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
	if (!fixed)
	{
	setX(getX() + getxVel());
	setY(getY() + getyVel());
	}
}
void Rect::calcNewPos(Point _p) {

}
bool Rect::getFixed()
{
	return fixed;
}

void Rect::setPosition(Point _p)
{
	position = _p;
}

void Rect::draw()
{

	gfx->FillRect(position, width, height, 0.5f, 0.5f, 0.5f, 1.0f);
	//gfx->DrawRect(position, width, height, 1.0f, 1.0f, 1.0f, 0.5f);
}

void Rect::load()
{

}
int Rect::getWeaponOffsetX() { return 0; }
int Rect::getWeaponOffsetY() { return 0; }

rectType Rect::getType()
{
	return type;
}

void Rect::ggravity(float _g)
{
	yVel = +_g;
}

bool Rect::getGravity()
{
	return gravity;
}

void Rect::addWeapon(Gun* _gun) {}