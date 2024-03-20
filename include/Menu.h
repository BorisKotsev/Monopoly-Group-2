#pragma once

#include "defines.h"
#include "State.h"
#include "Button.h"

class Menu : public State
{
public:
	Menu();
	~Menu();

	void init();
	void run();
	void destroy();
	bool playPressed=false;
private:
	Drawable m_background;
	Button exitButton;
	Button playButton;
	Button playersButton[3];
};