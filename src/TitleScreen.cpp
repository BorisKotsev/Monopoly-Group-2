#include "TitleScreen.h"
#include "World.h"

extern World world;

TitleScreen::TitleScreen()
{

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::init()
{
	fstream stream;
	string tmp, titleScreen, Continue;
	stream.open(CONFIG_FOLDER + "TitleScreen.txt");
	stream >> tmp >> titleScreen;
	stream >> tmp >> Continue;
	stream >> tmp >> m_pressToContinue.rect.x >> m_pressToContinue.rect.y >> m_pressToContinue.rect.w >> m_pressToContinue.rect.h;
	stream >> tmp >> m_pressToContinue.opacity;
	stream >> tmp >> m_pressToContinue.changePerFrame;
	stream.close();
	m_titleScreenLogo= loadTexture(TITLESCREEN_FOLDER+titleScreen);
	m_pressToContinue.texture= loadTexture(TITLESCREEN_FOLDER+ Continue);
}

void TitleScreen::run()
{
	drawObject(m_titleScreenLogo);
	drawObject(m_pressToContinue);

	if (isAnyKeyPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::MENU);
		return;
	}
	changeOpacity();
	cout << m_pressToContinue.opacity << endl;
}

void TitleScreen::destroy()
{
	SDL_DestroyTexture(m_titleScreenLogo);
	SDL_DestroyTexture(m_pressToContinue.texture);
}

void TitleScreen::changeOpacity()
{
	m_pressToContinue.opacity += m_pressToContinue.changePerFrame;
	if (m_pressToContinue.opacity >= 255)
	{
		m_pressToContinue.opacity = 255;
		m_pressToContinue.changePerFrame *= -1;
	}
	if (m_pressToContinue.opacity <= 55)
	{
		m_pressToContinue.opacity = 55;
		m_pressToContinue.changePerFrame *= -1;
	}
}
