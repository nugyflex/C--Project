#pragma once
#include "gun.h"

class pistol : public Gun
{
public:
	pistol(float _x, float _y, Graphics * gfx);
	~pistol();
	void load() override;
};
