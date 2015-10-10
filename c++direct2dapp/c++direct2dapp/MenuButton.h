#pragma once
#include "button.h"
class MenuButton: public Button {
public:
	MenuButton();
	~MenuButton();
	void action() override;
	void draw() override;

};