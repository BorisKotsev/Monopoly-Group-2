#pragma once
#include "Engine.h"
#include "District.h"
#include "Station.h"
#include "Question.h"
#include "Button.h"

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
	int m_winner = 1;

	void drawDice(int2 diceValue);
	void loadDices();
	void loadTurnUI();//player x on turn

	int2 roll();
	int2 diceValue;
	int playersAmount;
private:
	SDL_Texture* m_background;

	void loadDistricts();
	void loadStations();
	void loadQuestions();


	Question drawQuestion();
	Button m_Roll;
	Drawable m_Dice1;
	Drawable m_Dice2;
	SDL_Texture* m_dice[6];
	Drawable m_TurnUi;
	SDL_Texture* m_turnUi[4];
	int playerTurn = 1;

};