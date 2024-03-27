#pragma once

#include "defines.h"
#include "State.h"

class TitleScreen : public State
{
public:
	TitleScreen();
	~TitleScreen();

	void init();
	void run();
	void destroy();

private:
	void changeOpacity();
	SDL_Texture* m_titleScreenLogo;
	DrawableWithOpacity m_pressToContinue;
};