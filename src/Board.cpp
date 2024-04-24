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

}

void Board::update()
{
	m_Roll.update();
	if (m_Roll.isPressed())
	{
		diceValue.x = roll().x;
		diceValue.y = roll().y;

		drawDice(diceValue);

		m_players[playerTurn].movePlayer(diceValue);
		previousTurn = playerTurn;

		if (diceValue.x != diceValue.y)
		{
			playerTurn++;
		}

		if (playerTurn > playersAmount - 1)
			playerTurn = 0;
		m_TurnUi.texture = m_turnUi[playerTurn];
	}

	playerPosition(m_players[previousTurn]);
}

void Board::draw()
{
	drawObject(m_background);
  
	m_Roll.draw();
	drawObject(m_Dice1);
	drawObject(m_Dice2);
	drawObject(m_TurnUi);

	for (int i = 0; i < m_players.size(); i++) {
		m_players[i].draw();
	}

}

void Board::destroy()
{
	SDL_DestroyTexture(m_background);
	SDL_DestroyTexture(m_Dice1.texture);
	SDL_DestroyTexture(m_Dice2.texture);
	SDL_DestroyTexture(m_TurnUi.texture);
	m_Roll.destroy();
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
	string tmp;

	stream.open(CONFIG_FOLDER + "Turn.txt");
	stream >> tmp >> m_TurnUi.rect.x >> m_TurnUi.rect.y >> m_TurnUi.rect.w >> m_TurnUi.rect.h;
	stream.close();

	for (int i = 0; i < playersAmount; i++)
	{
		m_turnUi[i] = loadTexture(TURN_FOLDER + to_string(i+1) + ".bmp");
	}
	m_TurnUi.texture = m_turnUi[0];
}

void Board::playerPosition(Player playerOnTurn)
{
	playerOnTurn.m_player_location = boardLayout[playerOnTurn.currentmove];

	District tmp;
	Station tmp1;

	int not_district = 0;

	for (int i = 0; i < playerOnTurn.currentmove; i++) { //tape
		if (boardLayout[i] != 'd') {
			not_district++;
		}
	}


	switch (playerOnTurn.m_player_location)
	{

		case 'd': //district
			tmp = m_districts[(playerOnTurn.sideOfBoard * 6) + playerOnTurn.currentmove - not_district];
			break;

		case 's': //station
			tmp1 = m_stations[playerOnTurn.sideOfBoard]; //station stepped on
			break;

		case 't': //tax

			break;

		case 'q': //question
			drawQuestion(playerOnTurn);
			break;

		case 'e': //edge
			break;

		default:
			break;
	}

	cout << "Player location: " << playerOnTurn.m_player_location << "Player on turn:" << playerOnTurn.player_number << endl;
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

	vector<Question> questionVector;

	for (int i = 1; i <= numQuestions; i++) 
	{
		string tmp = "Question" + to_string(i) + ".txt";

		Question _question;

		_question.init(tmp);

		questionVector.push_back(_question);
	}

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(questionVector.begin(), questionVector.end(), default_random_engine(seed));

	for (const auto& question : questionVector) 
	{
		m_questions.push(question);
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

void Board::drawQuestion(Player playerOnTurn)
{
	if (!m_questions.empty())
	{
		m_questions.front().run();

		if (m_questions.front().m_answer == 1)
		{
			playerOnTurn.addMoney(m_questions.front().getMoney());

			Question tmp = m_questions.front();
			m_questions.pop();
			m_questions.push(tmp);
		}
		else if (m_questions.front().m_answer == 0)
		{
			playerOnTurn.removeMoney(m_questions.front().loseMoney());

			Question tmp = m_questions.front();
			m_questions.pop();
			m_questions.push(tmp);
		}
	}
	else
	{
		cout << "No questions left" << endl;
	}
}
