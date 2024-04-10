#include "Board.h"
#include "Presenter.h"
#include "InputManager.h"
#include "SoundManager.h"

Board::Board()
{

}

Board::~Board()
{

}

void Board::init()
{
    loadDistricts();
	loadStations();
	loadQuestions();
	loadPlayers();

	
	m_background = loadTexture("background.bmp");
	m_Roll.init("RollButton.txt","");

	loadDices();
	loadTurnUI();
	m_BuyPopUp.init("Borovo",100);
	//m_test.init("enterProduct.txt");
}

void Board::update()
{
//	m_test.update();
	m_playerTurn.update();
	m_Roll.update();
	m_playerTurn.setText(to_string(playerTurn+1));
	if (m_Roll.isPressed())
	{
		diceValue.x = roll().x;
		diceValue.y = roll().y;

		drawDice(diceValue);

		m_players[playerTurn].movePlayer(diceValue);

		if (diceValue.x != diceValue.y)
		{
			playerTurn++;
		}

		if (playerTurn > playersAmount - 1)
			playerTurn = 0;

		//m_test.setText(to_string(diceValue.x + diceValue.y));
	}
	cout<<m_BuyPopUp.Buy();
}

void Board::draw()
{
	drawObject(m_background);

	//m_test.draw();

	if (questionIndexTEST >= m_questions.size())
	{
		questionIndexTEST = 0;
	}

	m_questions[questionIndexTEST].run();

	if (m_questions[questionIndexTEST].m_answer == 1)
	{
		cout << m_questions[questionIndexTEST].getMoney() << endl;
		m_questions[questionIndexTEST].m_answer = -1;
		questionIndexTEST++;
	}
	else if (m_questions[questionIndexTEST].m_answer == 0)
	{
		cout << m_questions[questionIndexTEST].loseMoney() << endl;
		m_questions[questionIndexTEST].m_answer = -1;
		questionIndexTEST++;
	}
  
	m_Roll.draw();
	drawObject(m_Dice1);
	drawObject(m_Dice2);
	drawObject(m_TurnUi);
	m_playerTurn.draw();

	for (int i = 0; i < m_players.size(); i++) {
		m_players[i].draw();
	}
	m_BuyPopUp.draw();
}

void Board::destroy()
{
	SDL_DestroyTexture(m_background);
	SDL_DestroyTexture(m_Dice1.texture);
	SDL_DestroyTexture(m_Dice2.texture);
	SDL_DestroyTexture(m_TurnUi.texture);
	m_BuyPopUp.destroy();
	m_Roll.destroy();
	//m_test.destroy();
	m_playerTurn.destroy();
}


void Board::drawDice(int2 diceValue)
{
    /*int diceNum = 0;
	for (int i = 0; i < 10; i++)
	{
	
	m_Dice1.texture = m_dice[diceNum];
	m_Dice2.texture = m_dice[diceNum];
	drawObject(m_Dice1);
	drawObject(m_Dice2);

	diceNum++;
	if (diceNum >= 6)
		diceNum = 0;

	SDL_Delay(150);

	}*/
	    m_Dice1.texture = m_dice[diceValue.x-1];
		m_Dice2.texture = m_dice[diceValue.y-1];


}

void Board::loadDices()
{
	fstream stream;
	string tmp;

	stream.open(CONFIG_FOLDER + "Dice.txt");

	stream >> tmp >> m_Dice1.rect.x >> m_Dice1.rect.y >> m_Dice1.rect.w >> m_Dice1.rect.h;
	stream >> tmp >> m_Dice2.rect.x >> m_Dice2.rect.y >> m_Dice2.rect.w >> m_Dice2.rect.h;
	stream.close();

	for (int i = 0; i < 6; i++)
	{
		m_dice[i] = loadTexture(DICE_FOLDER + to_string(i+1) + ".bmp");
	}
	m_Dice1.texture = m_dice[0];
	m_Dice2.texture = m_dice[0];
}

void Board::loadTurnUI()
{
	fstream stream;
	string tmp,Turn;
	
	stream.open(CONFIG_FOLDER + "Turn.txt");
	stream >> tmp >> Turn;
	stream >> tmp >> m_TurnUi.rect.x >> m_TurnUi.rect.y >> m_TurnUi.rect.w >> m_TurnUi.rect.h;
	stream.close();

	m_TurnUi.texture = loadTexture(Turn);
	m_playerTurn.init("Turn.txt");
}

int2 Board::roll()
{
	int2 dice;

	dice.x = rand() % 6 + 1;
	dice.y = rand() % 6 + 1;

	return dice;
}

void Board::loadDistricts()
{
	fstream stream;
	string tmp;

	stream.open(CONFIG_FOLDER + "Districts.txt");

	while(!stream.eof())
	{
		stream >> tmp;

		District _district;

		_district.init(tmp);

		m_districts.push_back(_district);
	}

	stream.close();
}

void Board::loadStations()
{
	fstream stream;
	string tmp;

	stream.open(CONFIG_FOLDER + "stations.txt");

	while(!stream.eof())
	{
		stream >> tmp;

		Station _station;

		_station.init(tmp);

		m_stations.push_back(_station);
	}

	stream.close();
}

void Board::loadQuestions()
{
	int numQuestions = 26;

	for (int i = 1; i <= numQuestions; i++)
	{
		string tmp = "Question" + to_string(i) + ".txt";

		Question _question;

		_question.init(tmp);

		m_questions.push_back(_question);
	}
}

void Board::loadPlayers()
{
	for(int i = 1; i <= playersAmount; i++)
	{
		Player _player;

		_player.init("Player" + to_string(i) + ".txt", i);

		m_players.push_back(_player);
	}
}




