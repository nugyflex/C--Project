#include "pistol.h"
pistol::pistol(float _x, float _y, Graphics * gfx) :
	Gun(_x, _y, gfx)
{
}
pistol::~pistol()
{
}
void pistol::load()
{
	width = 12;
	height = 6;
	image = new SpriteSheet(L"pistol.png", 12, 6, 0, 1, gfx);
	hitMarker = new SpriteSheet(L"hitmarker.png", 11, 11, 0, 1, gfx);
	maxCooldown = 15;
	coolDown = 0;
	damage = 4;
	hasLatch = true;
}