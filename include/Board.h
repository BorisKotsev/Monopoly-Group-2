#pragma once

#include <cstdio>

#include "Engine.h"
#include "District.h"
#include "Station.h"
#include "Question.h"
#include "Button.h"
#include "Player.h"
#include "TextField.h"
#include "BuyPopUp.h"
#include "PopUpTax.h"
#include "PropertyBreach.h"

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

	void playerPosition(Player& playerOnTurn);
	char boardLayout[10] = { 'e', 'd', 't', 'd', 'd', 's', 'd', 'q', 'd', 'd' };
	int districtOwner(string);
	int stationOwner(string);

private:
	SDL_Texture* m_background;

	void loadDistricts();
	void loadStations();
	void loadQuestions();
	void loadPlayers();

	void drawQuestion(Player playerOnTurn);

	void winnerCheck();

	int2 diceValue;

	Button m_Roll;
	Button m_Exit;
	Drawable m_Dice1;
	Drawable m_Dice2;
	Drawable m_TurnUi;
	Drawable m_info;
	BuyPopUp* m_BuyDistrict;
	BuyPopUp* m_BuyStation;
	BuyPopUp* m_BuyHouses;
	PopUpTax* m_PayYourTaxes;
	Question* m_tmpQuestion;
	PropertyBreach* m_BreachPopUp;

	SDL_Texture* m_dice[6];
	int diceDoubles;
	int playerPrev;
	int playerTurn = 0;
	District m_tmpDistrict;
	Station m_tmpStation;
	int taxToPay = 0;
	
	TextField m_playerTurn;
	TextField m_playermoney;
	

	int previousTurn;

	bool canPressRoll = true;
};