#include "fireball.h"
#include "stdio.h"

FireBall::FireBall() {}

FireBall::FireBall(Point _position, float _yVel, float _xVel, Graphics * gfxi) :
	Rect(_position, 20, 20, _yVel, _xVel, false, fireball, false, gfxi)
{

}

FireBall::~FireBall()
{
}

void FireBall::draw()
{
	//dont forget you will need header file #include "stdio.h"
	//char s[200];
	//int x = 4;
	//sprintf_s(s, "this is my variable: %d.", x);
	//OutputDebugString(s);
	mainsprite->Draw(0, position.x-4, position.y-4);


}

void FireBall::load()
{

	mainsprite = new SpriteSheet(L"fireball.png", 28, 28, 0, 1, gfx);
}