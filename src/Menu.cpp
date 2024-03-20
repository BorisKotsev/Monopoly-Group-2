#include "Menu.h"
#include "World.h"
extern World world;

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::init()
{
	m_background.texture = loadTexture(MENU_FOLDER + "background.bmp");
	m_background.rect = { 0,0,1920,1080 };

	playButton.init("PlayButton.txt",MENU_FOLDER);
	exitButton.init("ExitButton.txt","");
	playersButton[0].init("2players.txt", MENU_FOLDER);
	playersButton[1].init("3players.txt", MENU_FOLDER);
	playersButton[2].init("4players.txt", MENU_FOLDER);
}

void Menu::run()
{
	drawObject(m_background);
	//draw buttons
	playButton.draw();
	exitButton.draw();
	//update buttons
	playButton.update();
	exitButton.update();


	if (exitButton.isPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
		return;
	}
	if (playPressed)
	{
		playersButton[0].draw();
		playersButton[1].draw();
		playersButton[2].draw();

		playersButton[0].update();
		playersButton[1].update();
		playersButton[2].update();

		
		if (playersButton[0].isPressed())
		{
			world.m_stateManager.m_game->m_board.playersAmount = 2;
			world.m_stateManager.changeGameState(GAME_STATE::GAME);
			return;
		}
		if (playersButton[1].isPressed())
		{
			world.m_stateManager.m_game->m_board.playersAmount = 3;
			world.m_stateManager.changeGameState(GAME_STATE::GAME);
			return;
		}
		if (playersButton[2].isPressed())
		{
			world.m_stateManager.m_game->m_board.playersAmount = 4;
			world.m_stateManager.changeGameState(GAME_STATE::GAME);
			return;
		}

	}
	else
	{
	if (playButton.isPressed())
	{
		playButton.destroy();
		playPressed = true;
		SDL_Delay(100);
	}

	}

}

void Menu::destroy()
{
	SDL_DestroyTexture(m_background.texture);
	exitButton.destroy();
	playButton.destroy();
	playersButton[0].destroy();
	playersButton[1].destroy();
	playersButton[2].destroy();
}