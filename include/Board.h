#pragma once
#include "Engine.h"
#include "District.h"
#include "Station.h"
#include "Question.h"
#include "Player.h"

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

	vector <Player> m_players;

	int m_winner = 1;

	Player player_a;

	void drawDice(int2 diceValue);
	void loadDices();
	void loadTurnUI();//player x on turn

	int2 roll();

	int playersAmount = 4;
private:
	SDL_Texture* m_background;

	void loadDistricts();
	void loadStations();
	void loadQuestions();
	void loadPlayers();

	int2 diceValue;

	Drawable m_Roll;
	Drawable m_Dice1;
	Drawable m_Dice2;
	Drawable m_TurnUi;

	SDL_Texture* m_dice[6];
	SDL_Texture* m_turnUi[4];

	int playerTurn = 1;

	int questionIndexTEST = 0;
};