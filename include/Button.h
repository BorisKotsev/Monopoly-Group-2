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
	void Increase();
	bool isPressed();
	int counter = 0; //related to increase() - counts until equal to maxIncrease
	bool m_isClicked = false;
	int maxIncrease = 15;
	int increasePerFrame = 5;

	Drawable m_button;
private:
};