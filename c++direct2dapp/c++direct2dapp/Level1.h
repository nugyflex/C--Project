#pragma once

#include "GameLevel.h"
#include "CollisionDetection.h"
#include "GameController.h"
#include "Graphics.h"





class Level1 : public GameLevel
{
	float y;
	float yVel;
	int soundLatch;
	int testvar;
	int fc;
	bool paused;
	Camera* camera;
	SpriteSheet* backGround;
	vector<Button*> buttons;
	vector<Gun*> weapons;

public:

	void Load() override;
	void Unload() override;
	void Render();
	void Update();

};