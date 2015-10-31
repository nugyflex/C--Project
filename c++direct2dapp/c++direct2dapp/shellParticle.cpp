#include "shellParticle.h"

shellParticle::shellParticle(Point _position, Graphics* _gfx, float _xvel, float _yvel)
{
	gfx = _gfx;
	position = _position;
	xVel = _xvel;
	yVel = _yvel;
}

shellParticle::~shellParticle() {}

void shellParticle::load()
{
	hasGravity = true;
	gravity = 0.6;
	despawnTimer = 40;
	image = new SpriteSheet(L"shellSpriteSheet.png", 6, 2, 0, 1, gfx);
	frame = rand() % 6 + 1;
	width = 6;
	height = 5;
	maxvel = 4.9;
	rotation = (rand() % 20 + 1);
	rotation = rotation / 20;
	rotation -= 0.5;
}
void shellParticle::draw()
{
	gfx->rotate(position, rotation);
	image->Draw(frame, 0, 3);
	gfx->rotateBack(position, 0);
}