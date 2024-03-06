#pragma once

#include "defines.h"
#include "State.h"

class WinScreen : public State
{
public:
	WinScreen();
	~WinScreen();

	void init();
	void run();
	void destroy();
private:
	Drawable m_background;
};