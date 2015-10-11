#pragma once
#include "button.h"
class Level1Button : public Button {
public:
	Level1Button();
	Level1Button(int _x, int _y, Graphics * gfxi);
	~Level1Button();

	void action() override;
	void draw() override;

};