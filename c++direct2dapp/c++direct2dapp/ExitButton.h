#pragma once
#include "button.h"
class ExitButton : public Button {
public:
	ExitButton();
	ExitButton(int _x, int _y, Graphics * gfxi);
	~ExitButton();

	void action() override;
	void draw() override;

};