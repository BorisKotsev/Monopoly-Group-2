#include "WinScreen.h"
#include "World.h"

WinScreen::WinScreen()
{
	//ctor
}

WinScreen::~WinScreen()
{
	//dtor
}

void WinScreen::init()
{
	m_background.texture = loadTexture("Null.bmp");

	m_background.rect = { 0, 0, 1920, 1080 };
}

void WinScreen::run()
{
	drawObject(m_background);
}

void WinScreen::destroy()
{
	SDL_DestroyTexture(m_background.texture);
}