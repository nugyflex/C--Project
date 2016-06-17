#pragma once

#include "CollisionDetection.h"
#include "gameController.h"
#include "Graphics.h"
#include "tinyxml2.h"
//#include "levelEditor.h"////
using namespace tinyxml2;
class playableLevel : public gameLevel
{
protected:
	//levelEditor LevelEditor;////
	float y;
	float yVel;
	bool qLatch;
	Camera* camera;
	SpriteSheet* backGround;
	vector<Gun*> weapons;
	particleCollection *particles;
	projectileCollection *projectiles;
	int playerIndex;
	Point boundaryOut;
	Point boundaryIn;
	tinyxml2::XMLDocument doc;
	const char* xmlPath;
	char tempchar[1000];
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
	void HandleInput() override;
	void addPlatformFromXML(XMLElement* _parsedxml);
	void addAllPlatformsFromXML();
	virtual void loadObjects();
	void addDroneFromXML(XMLElement* _parsedxml);
	void addAllDronesFromXML();
	void addExitPointFromXML(XMLElement* _parsedxml);
	Point getPlayerPositionFromXML();
};