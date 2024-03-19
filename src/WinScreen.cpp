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


	m_exit.init("ExitButton.txt","");
	m_playAgain.init("PlayAgainButton.txt", WINSCREEN_FOLDER);
}

void WinScreen::run()
{
	drawObject(m_background);
	m_exit.draw();
	m_playAgain.draw();

	m_exit.update();
	m_playAgain.update();
	if (m_playAgain.isPressed())
	{
			world.m_stateManager.changeGameState(GAME_STATE::MENU);
			return;
	}

	if (m_exit.isPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
		return;
	}

}

void WinScreen::destroy()
{
	SDL_DestroyTexture(m_background.texture);
	m_exit.destroy();
	m_playAgain.destroy();
}