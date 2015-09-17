#include "Player.h"
#include "stdio.h"

Player::Player() {}

Player::Player(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics * gfxi):
Rect(_position, _width, _height, _yVel, _xVel, false, player, gfxi)
{

}

Player::~Player()
{
}

void Player::draw()
{
	//dont forget you will need header file #include "stdio.h"
	//char s[200];
	//int x = 4;
	//sprintf_s(s, "this is my variable: %d.", x);
	//OutputDebugString(s);

	if (yVel == 0)
	{
		if (xVel < 0)
		{
			spritewalkingleft->autoSwitchFrame(10);
			spritewalkingleft->Draw(-1, position.x, position.y);
			lastdirection = 0;
		}
		if (xVel > 0)
		{
			spritewalkingright->autoSwitchFrame(10);
			spritewalkingright->Draw(-1, position.x, position.y);
			lastdirection = 1;
		}
		if (xVel == 0)
		{
			if (lastdirection == 0)
			{
				spritestandingleft->Draw(0, position.x, position.y);
			}
			if (lastdirection == 1)
			{
				spritestandingright->Draw(0, position.x, position.y);
			}
		}
	}
	else
	{
		if (xVel > 0)
		{
			spritewalkingright->Draw(0, position.x, position.y);
			lastdirection = 1;
		}
		if (xVel < 0)
		{
			spritewalkingleft->Draw(0, position.x, position.y);
			lastdirection = 0;
		}
		if (xVel == 0)
		{
			if (lastdirection == 0)
			{
				spritewalkingleft->Draw(0, position.x, position.y);
			}
			if (lastdirection == 1)
			{
				spritewalkingright->Draw(0, position.x, position.y);
			}
		}

	}
	
}

void Player::load()
{
	lastdirection = 1;
	spritewalkingleft = new SpriteSheet(L"walkingleftnobags.png", 32, 54, 0, 4, gfx);
	spritewalkingright = new SpriteSheet(L"walkingrightwithbags.png", 32, 54, 0, 4, gfx);
	spritestandingleft = new SpriteSheet(L"standingleft.png", 32, 54, 0, 1, gfx);
	spritestandingright = new SpriteSheet(L"standingright.png", 32, 54, 0, 1, gfx);
	spritejumpingleft = new SpriteSheet(L"jumpingleft.png", 32, 54, 0, 1, gfx);
	spritejumpingright = new SpriteSheet(L"sanddunes.png", 1280, 720, 0, 1, gfx);
}