#pragma once
#include "Engine.h"
#include "District.h"
#include "Station.h"
#include "Question.h"

class Board
{
public:
	Board();
	~Board();

	void init();
	void update();
	void draw();
	void destroy();

	vector <District> m_districts;
	vector <Station> m_stations;
	vector <Question> m_questions;

	void drawDice(int2 diceValue);
	void loadDices();
	int2 roll();
	int2 diceValue;
private:
	SDL_Texture* m_background;

	void loadDistricts();
	void loadStations();
	void loadQuestions();

	Question drawQuestion();
	Drawable m_Roll;
	Drawable m_Dice1;
	Drawable m_Dice2;
	SDL_Texture* m_dice[6];
};