#include "sparkParticle.h"

sparkParticle::sparkParticle(Point _position, Graphics* _gfx)
{
	gfx = _gfx;
	position = _position;
}

sparkParticle::~sparkParticle(){}

void sparkParticle::load()
{
	hasGravity = true;
	gravity = 0.05;
	despawnTimer = 120;
	image = new SpriteSheet(L"gun1.png", 20, 10, 0, 1, gfx);
}
void sparkParticle::draw()
{
	gfx->DrawLine(position, Point{ position.x + 7, position.y + 7 }, 1, 1, 0, 20.6);
}