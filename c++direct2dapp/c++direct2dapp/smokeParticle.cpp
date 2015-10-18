#include "SmokeParticle.h"

smokeParticle::smokeParticle(Point _position, Graphics* _gfx)
{
	gfx = _gfx;
	position = _position;
	xVel = 0;
}

smokeParticle::~smokeParticle() {}

void smokeParticle::load()
{
	hasGravity = true;
	gravity = -0.05;
	despawnTimer = 240;
	image = new SpriteSheet(L"smokeSpriteSheet.png", 10, 10, 0, 1, gfx);
	frame = rand() % 5 + 1;
	width = 10;
	height = 10;
	maxvel = 2;
}
void smokeParticle::draw()
{
	image->Draw(frame, position.x, position.y);
	//gfx->DrawLine(position, Point{ position.x + 7, position.y + 7 }, 1, 1, 0, 20.6);
}