#include "Player.h"

Player::Player() {}

Player::Player(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics * gfxi):
Rect(_position, _width, _height, _yVel, _xVel, false, gfxi)
{
	sprite = new SpriteSheet(L"walkingleftwithbags.png", 32, 54, 0, 4, gfxi);
}

Player::~Player()
{
}
/*
void Player::draw()
{

}*/