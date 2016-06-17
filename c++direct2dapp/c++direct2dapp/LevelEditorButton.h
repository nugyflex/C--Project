#pragma once
#include "button.h"
class LevelEditorButton : public Button {
public:
	LevelEditorButton();
	LevelEditorButton(int _x, int _y, Graphics * gfxi);
	~LevelEditorButton();

	void action() override;
	void draw() override;
};