#include "Player.h"
#include "stdio.h"

Player::Player() {}

Player::Player(Point _position, float _width, float _height, float _yVel, float _xVel, Graphics * gfxi) :
	Rect(_position, _width, _height, _yVel, _xVel, false, player, true, gfxi)
{
}

Player::~Player()
{
}

void Player::draw()
{
	if (crouched && !lastCrouched)
	{
		height = 33;
		position.y += 19;
	}
	else
	{
		if (!crouched && lastCrouched)
		{
			height = 54;
			position.y -= 19;
		}
	}
	if (hasBags)
	{
		if (yVel == 0)
		{
			if (xVel < 0)
			{
				spritewalkingleftwithbags->autoSwitchFrame(10);
				spritewalkingleftwithbags->Draw(-1, position.x, position.y);
				lastdirection = 0;
			}
			if (xVel > 0)
			{
				spritewalkingrightwithbags->autoSwitchFrame(10);
				spritewalkingrightwithbags->Draw(-1, position.x, position.y);
				lastdirection = 1;
			}
			if (xVel == 0)
			{
				if (lastdirection == 0)
				{
					spritestandingleftwithbags->Draw(0, position.x, position.y);
				}
				if (lastdirection == 1)
				{
					spritestandingrightwithbags->Draw(0, position.x, position.y);
				}
			}
		}
		else
		{
			if (xVel > 0)
			{
				spritewalkingrightwithbags->Draw(0, position.x, position.y);
				lastdirection = 1;
			}
			if (xVel < 0)
			{
				spritewalkingleftwithbags->Draw(0, position.x, position.y);
				lastdirection = 0;
			}
			if (xVel == 0)
			{
				if (lastdirection == 0)
				{
					spritewalkingleftwithbags->Draw(0, position.x, position.y);
				}
				if (lastdirection == 1)
				{
					spritewalkingrightwithbags->Draw(0, position.x, position.y);
				}
			}
		}
	}
	else
	{
		if (yVel == 0)
		{
			if (xVel < 0)
			{
				spritewalkingleft->autoSwitchFrame(10);
				spritewalkingleft->Draw(-1, position.x - 9, position.y);
				lastdirection = 0;
			}
			if (xVel > 0)
			{
				spritewalkingright->autoSwitchFrame(10);
				spritewalkingright->Draw(-1, position.x - 9, position.y);
				lastdirection = 1;
			}
			if (xVel == 0)
			{
				if (!crouched)
				{
					if (lastdirection == 0)
					{
						spritestandingleft->Draw(0, position.x - 9, position.y);
					}
					if (lastdirection == 1)
					{
						spritestandingright->Draw(0, position.x - 9, position.y);
					}
				}
				else
				{
					if (lastdirection == 0)
					{
						spritecrouchingleft->Draw(0, position.x - 9, position.y);
					}
					if (lastdirection == 1)
					{
						spritecrouchingright->Draw(0, position.x - 9, position.y);
					}
				}
			}
		}
		else
		{
			if (!crouched)
			{
				if (xVel > 0)
				{
					spritewalkingright->Draw(3, position.x - 9, position.y);
					lastdirection = 1;
				}
				if (xVel < 0)
				{
					spritewalkingleft->Draw(3, position.x - 9, position.y);
					lastdirection = 0;
				}
				if (xVel == 0)
				{
					if (lastdirection == 0)
					{
						spritewalkingleft->Draw(3, position.x - 9, position.y);
					}
					if (lastdirection == 1)
					{
						spritewalkingright->Draw(3, position.x - 9, position.y);
					}
				}
			}
			else
			{
				if (lastdirection == 0)
				{
					spritecrouchingleft->Draw(0, position.x - 9, position.y);
				}
				if (lastdirection == 1)
				{
					spritecrouchingright->Draw(0, position.x - 9, position.y);
				}
			}
		}
	}
	gfx->FillRect(Point{ position.x - 5, position.y - 10 }, health * 5, 5, 1, 1, 1, 1);
	lastCrouched = crouched;
	if (vel == 5)
	{
		sprinting = true;
	}
	else
	{
		sprinting = false;
	}
}

void Player::load()
{
	lastdirection = 1;
	spritewalkingleft = new SpriteSheet(L"walkingleftnobags.png", 32, 54, 0, 4, gfx);
	spritewalkingright = new SpriteSheet(L"walkingrightnobags.png", 32, 54, 0, 4, gfx);
	spritestandingleft = new SpriteSheet(L"standingleft.png", 32, 54, 0, 1, gfx);
	spritestandingright = new SpriteSheet(L"standingright.png", 32, 54, 0, 1, gfx);
	spritecrouchingleft = new SpriteSheet(L"crouchingleft.png", 32, 54, 0, 1, gfx);
	spritecrouchingright = new SpriteSheet(L"crouchingright.png", 32, 54, 0, 1, gfx);
	spritewalkingleftwithbags = new SpriteSheet(L"walkingleftwithbags.png", 32, 54, 0, 4, gfx);
	spritewalkingrightwithbags = new SpriteSheet(L"walkingrightwithbags.png", 32, 54, 0, 4, gfx);
	spritestandingleftwithbags = new SpriteSheet(L"standingleftwithbags.png", 32, 54, 0, 1, gfx);
	spritestandingrightwithbags = new SpriteSheet(L"standingrightwithbags.png", 32, 54, 0, 1, gfx);
	weaponInUse = 0;
	hasBags = false;
	health = 6;
	invulnerable = false;
	crouched = false;
	width = 12;
	height = 54;
	vel = 3;
}
int Player::getWeaponOffsetY()
{
	return 22;
}
int Player::getWeaponOffsetX()
{
	return 9;
}
void Player::addWeapon(Gun* _gun)
{
	weapons.push_back(_gun);
	weaponInUse = weapons.size() - 1;
}
int Player::getWeaponInUse()
{
	return weaponInUse;
}
Point Player::getWeaponPos()
{
	return Point{ position.x + getWeaponOffsetX(), position.y + getWeaponOffsetY() };
}
void Player::subtractHealth(int _amount)
{
	health -= _amount;
}
int Player::getHealth()
{
	return health;
}
bool Player::getInvulnerable()
{
	return invulnerable;
}
void Player::setInvulnerable(bool _b)
{
	invulnerable = _b;
}
bool Player::getCrouched()
{
	return crouched;
}
void Player::setCrouched(bool _bool)
{
	crouched = _bool;
}
int Player::getVel()
{
	return vel;
}
void Player::setVel(int _vel)
{
	vel = _vel;
}
bool Player::getSprinting()
{
	return sprinting;
}