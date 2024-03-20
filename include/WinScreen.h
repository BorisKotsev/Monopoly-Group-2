#pragma once

#include "defines.h"
#include "State.h"
#include "Button.h"

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
	Button  m_exit;
	Button m_playAgain;
};