#include "sparkParticle.h"

sparkParticle::sparkParticle(Point _position, Graphics* _gfx, float _xvel)
{
	gfx = _gfx;
	position = _position;
	xVel = _xvel;
}

sparkParticle::~sparkParticle(){}

void sparkParticle::load()
{
	hasGravity = true;
	gravity = 0.5;
	despawnTimer = 360;
	image = new SpriteSheet(L"sparkSpriteSheet.png", 5, 5, 0, 1, gfx);
	frame = rand() % 6 + 1;
	width = 5;
	height = 5;
	maxvel = 4.9;
}
void sparkParticle::draw()
{
	image->Draw(frame, position.x, position.y);
	//gfx->DrawLine(position, Point{ position.x + 7, position.y + 7 }, 1, 1, 0, 20.6);
}