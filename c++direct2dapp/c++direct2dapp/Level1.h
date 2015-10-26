#pragma once

#include "gameLevel.h"
#include "CollisionDetection.h"
#include "gameController.h"
#include "Graphics.h"
#include <fstream>

class Level1 : public gameLevel 
{
	float y;
	float yVel;
	int soundLatch;
	int testvar;
	int fc;
	Camera* camera;
	SpriteSheet* backGround;
	vector<Button*> buttons;
	vector<Gun*> weapons;
	particleCollection *particles;
	ofstream saveFileOut;
	ifstream saveFileIn;
public:

	void Load() override;
	void Unload() override;
	void Render();
	void Update();

};