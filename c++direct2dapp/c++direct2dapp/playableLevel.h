#pragma once

#include "CollisionDetection.h"
#include "gameController.h"
#include "Graphics.h"

class playableLevel : public gameLevel
{
protected:
	float y;
	float yVel;
	Camera* camera;
	SpriteSheet* backGround;
	vector<Button*> buttons;
	vector<Gun*> weapons;
	vector<exitPoint*> exitPoints;
	particleCollection *particles;
	projectileCollection *projectiles;
	int playerIndex;
	Point boundaryOut;
	Point boundaryIn;
public:
	void Load() override;
	void Unload() override;
	void Render();
	void Update();
	virtual void loadObjects();
};