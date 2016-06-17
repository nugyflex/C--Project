#pragma once
#include "gun.h"
#include "button.h"
#include "exitPoint.h"
#include "Platform.h"
#include "tinyxml2.h"
#include "spy.h"
#include "hunter.h"
enum editorAction {deleteRect, deletePlayer, deleteExitPoint, addRect, addExitPoint, addPlayer};
class levelEditor
{
private:
	Point startOfRect;
	Graphics *gfx;
	editorMode mode;
	bool buttonHasBeenCLicked;
	Point mouseDragOffSet;
	bool lastshift;
	bool snapToGrid;
	bool lastZ;
	bool lastS;
	int snapInterval;
	bool isPlayer;
	int lastObjectID;
	const char* xmlPath = "testfile.xml";
	char tempchar[6000];
	tinyxml2::XMLDocument doc;
	int numberOfPlatforms = 0;
	int numberOfDrones = 0;
	bool showGrid;
	vector<editorAction> editorActions;
	vector<int> actionIndexes;
	vector<int> rectStatus;
	vector<int> exitPointStatus;
	bool itemDeleted;
public:
	levelEditor(Graphics* _gfx);
	levelEditor();
	~levelEditor();
	void saveAsNewLevel();
	void update();
	void draw();
	bool doesExist(const char *name);
	void load();
	void addPlayerPositionToXML(Rect* _player);
	void addExitPointToXML(exitPoint* _exitpoint);
	void addPlatformToXML(Rect* _platform);
	void addDroneToXML(Drone* _drone);
	int getNextOID();
};