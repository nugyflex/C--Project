#pragma once

#include "GameLevel.h"

class Level1 : public GameLevel
{
	float y;
	float yVel;

public:

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
};