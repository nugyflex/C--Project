#pragma once
#pragma once

#include "gameLevel.h"
#include "CollisionDetection.h"
#include "gameController.h"
#include "Graphics.h"

class Menu : public gameLevel
{
public:
	void HandleInput() override;
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
};