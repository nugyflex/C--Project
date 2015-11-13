#pragma once
#include "gun.h"

class assaultRifle : public Gun
{
public:
	assaultRifle(float _x, float _y, Graphics * gfx);
	~assaultRifle();
	void load() override;
};