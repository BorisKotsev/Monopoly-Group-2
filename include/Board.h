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
	queue <Question> m_questions;

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

	void drawQuestion(Player playerOnTurn);

	int2 diceValue;

	Button m_Roll;
	Drawable m_Dice1;
	Drawable m_Dice2;
	Drawable m_TurnUi;
	BuyPopUp* m_BuyDistrict;
	BuyPopUp* m_BuyStation;

	SDL_Texture* m_dice[6];
	int playerPrev;
	int playerTurn = 0;
	District m_tmpDistrict;
	Station m_tmpStation;
	
	TextField m_playerTurn;
	int playerTurn = 0;
	int previousTurn;
};