#include "Platform.h"

Platform::Platform() {}

Platform::Platform(Point _position, int _width, int _height, float _yVel, float _xVel, Graphics * gfxi) :
	Rect(_position, _width, _height, _yVel, _xVel, true, platform, gfxi)
{

}

Platform::~Platform()
{
}
