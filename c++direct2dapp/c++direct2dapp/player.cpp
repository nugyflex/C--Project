#include "Player.h"

Player::Player() {}

Player::Player(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics * gfxi):
Rect(_position, _width, _height, _yVel, _xVel, false, gfxi)
{

}

Player::~Player()
{
}

void Player::draw()
{
	if (xVel < 0)
	{
		spritewalkingleft->autoSwitchFrame(10);
		spritewalkingleft->Draw(0, position.x, position.y);
	}
	if (xVel > 0)
	{
		spritewalkingright->autoSwitchFrame(10);
		spritewalkingright->Draw(0, position.x, position.y);
	}
}

void Player::load()
{

	spritewalkingleft = new SpriteSheet(L"walkingleftwithbags.png", 32, 54, 0, 4, gfx);
	spritewalkingright = new SpriteSheet(L"walkingrightwithbags.png", 32, 54, 0, 4, gfx);
}