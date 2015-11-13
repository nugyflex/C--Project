#include "assaultRifle.h"
assaultRifle::assaultRifle(float _x, float _y, Graphics * gfx) :
	Gun(_x, _y, gfx)
{
}
assaultRifle::~assaultRifle()
{
}
void assaultRifle::load()
{
	width = 25;
	height = 8;
	image = new SpriteSheet(L"scar-h.png", 25, 8, 0, 1, gfx);
	hitMarker = new SpriteSheet(L"hitmarker.png", 11, 11, 0, 1, gfx);
	maxCooldown = 5;
	coolDown = 0;
	damage = 2;
	hasLatch = false; 
}