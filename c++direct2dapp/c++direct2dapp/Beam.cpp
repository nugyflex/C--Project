#include "Beam.h"


Beam::Beam(Point _p1, Point _p2, vector<Rect*> &_Rects)
{
	Rects = _Rects;
	p1 = _p1;
	p2 = _p2;
}
Beam::~Beam()
{

}