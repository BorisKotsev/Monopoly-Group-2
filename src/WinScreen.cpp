#include "WinScreen.h"
#include "World.h"
WinScreen::WinScreen()
{
}

WinScreen::~WinScreen()
{
}

void WinScreen::init()
{
	m_background.rect = {0,0,1920,1080};
	m_background.texture = loadTexture(WINSCREEN_FOLDER+"WinScreen.bmp");
	fstream stream;
	string tmp,exit,PA;//PA-play again
	stream.open(CONFIG_FOLDER+"WinScreen.txt");
	stream >> tmp >> exit;
	stream >> tmp >> m_exit.rect.x >> m_exit.rect.y >> m_exit.rect.w >> m_exit.rect.h;
	stream >> tmp >> PA;
	stream >> tmp >> m_playAgain.rect.x >> m_playAgain.rect.y >> m_playAgain.rect.w >> m_playAgain.rect.h;
	stream.close();
	m_exit.texture = loadTexture(exit);
	m_playAgain.texture = loadTexture(PA);

}

void WinScreen::run()
{
	drawObject(m_background);
	drawObject(m_exit);
	drawObject(m_playAgain);
	if (isMouseInRect(InputManager::m_mouseCoor, m_playAgain.rect)&& InputManager::isMousePressed())
	{
			world.m_stateManager.changeState(GAME_STATES::GAME);
			return;
	}

	if (isMouseInRect(InputManager::m_mouseCoor, m_exit.rect) && InputManager::isMousePressed())
	{
		destroy();
	}

}

void WinScreen::destroy()
{
	SDL_DestroyTexture(m_background.texture);
	SDL_DestroyTexture(m_exit.texture);
	SDL_DestroyTexture(m_PA.texture);
}
