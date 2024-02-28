#pragma once
#include "Engine.h"

class Board
{
public:
	Board();
	~Board();

	void init();
	void update();
	void draw();
	void destroy();
	void drawDice(int2 diceValue);
	void loadDices();
	int2 roll();
	int2 diceValue;
private:
	SDL_Texture* m_background;
	Drawable m_Roll;
	Drawable m_Dice1;
	Drawable m_Dice2;
	SDL_Texture* m_dice[6];
};