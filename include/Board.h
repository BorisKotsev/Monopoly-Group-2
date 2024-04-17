#pragma once
#include "Engine.h"
#include "District.h"
#include "Station.h"
#include "Question.h"
#include "Button.h"
#include "Player.h"
#include "TextField.h"
#include "BuyPopUp.h"

//bool buy = false;
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

	//bool buy;
	int2 roll();
	int playersAmount;

	void playerPosition(Player playerOnTurn);
	char boardLayout[10] = { 'e', 'd', 't', 'd', 'd', 's', 'd', 'q', 'd', 'd' };

private:
	SDL_Texture* m_background;

	void loadDistricts();
	void loadStations();
	void loadQuestions();
	void loadPlayers();

	int2 diceValue;

	Button m_Roll;
	Drawable m_Dice1;
	Drawable m_Dice2;
	Drawable m_TurnUi;
	BuyPopUp m_BuyPopUp;

	SDL_Texture* m_dice[6];
	
	int playerTurn =0;
	int questionIndexTEST = 0;

	//TextField m_test;
	TextField m_playerTurn;
};