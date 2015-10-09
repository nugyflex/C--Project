#pragma once
#pragma once

#include "GameLevel.h"
#include "CollisionDetection.h"
#include "GameController.h"
#include "Graphics.h"





class Menu : public GameLevel
{

public:

	void Load() override;
	void Unload() override;
	void Render();
	void Update();
};