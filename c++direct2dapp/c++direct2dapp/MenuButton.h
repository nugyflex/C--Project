#pragma once
#include "button.h"
class MenuButton: public Button {
public:
	MenuButton();
	MenuButton(int _x, int _y, Graphics * gfxi);
	~MenuButton();
	
	void action() override;
	void draw() override;
	
};