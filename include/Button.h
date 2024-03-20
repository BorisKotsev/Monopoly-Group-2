#pragma once
#include "defines.h"

class Button
{
public:
	Button();
	~Button();

	void init(string config,string folder);
	void draw();
	void update();
	void destroy();
	bool isPressed();

private:
	int counter; //related to increase() - counts until equal to maxIncrease
	bool m_isClicked;
	int maxIncrease;
	int increasePerFrame;
	Drawable m_button;
};