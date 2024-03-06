#include "WinScreen.h"
	#include "World.h"
	extern World world;

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
	int winner = world.m_stateManager.m_game->m_board.m_winner;
	winner = 2; //test
	m_background.rect = {0,0,1920,1080};
	string file = "background" + to_string(winner) + ".bmp";
	m_background.texture = loadTexture(WINSCREEN_FOLDER+file);
	fstream stream;
	string tmp,exit,PA;//PA-play again
	stream.open(CONFIG_FOLDER+"WinScreen.txt");
	stream >> tmp >> exit;
	stream >> tmp >> m_exit.rect.x >> m_exit.rect.y >> m_exit.rect.w >> m_exit.rect.h;
	stream >> tmp >> PA;
	stream >> tmp >> m_playAgain.rect.x >> m_playAgain.rect.y >> m_playAgain.rect.w >> m_playAgain.rect.h;
	stream.close();
	m_exit.texture = loadTexture(WINSCREEN_FOLDER+exit);
	m_playAgain.texture = loadTexture(WINSCREEN_FOLDER+PA); 
}

void WinScreen::run()
{
	drawObject(m_background);
	drawObject(m_exit);
	drawObject(m_playAgain);
	if (isMouseInRect(InputManager::m_mouseCoor, m_playAgain.rect)&& InputManager::isMousePressed())
	{
			world.m_stateManager.changeGameState(GAME_STATE::GAME);
			return;
	}

	if (isMouseInRect(InputManager::m_mouseCoor, m_exit.rect) && InputManager::isMousePressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
		return;
	}

}

void WinScreen::destroy()
{
	SDL_DestroyTexture(m_background.texture);
	SDL_DestroyTexture(m_exit.texture);
	SDL_DestroyTexture(m_playAgain.texture);
}