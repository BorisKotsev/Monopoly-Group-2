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
	string configFile = "boardInit.txt";

	fstream stream;

	string backgorundImg,rollButton, tmp;

	stream.open(CONFIG_FOLDER + configFile);

    stream >> tmp >> backgorundImg;
    stream >> tmp >> rollButton;
    stream >> tmp >> m_Roll.rect.x >> m_Roll.rect.y >> m_Roll.rect.w >> m_Roll.rect.h;

	stream.close();

	m_background = loadTexture(backgorundImg);
	m_Roll.texture = loadTexture(rollButton);
	loadDices();
}

void Board::update()
{
		
	if (isMouseInRect(InputManager::m_mouseCoor, m_Roll.rect) && InputManager::isMousePressed())
	{
		diceValue.x = roll().x;
		diceValue.y = roll().y;
	    drawDice(diceValue);
	}
		
}

void Board::draw()
{
	drawObject(m_background);
	drawObject(m_Roll);
	drawObject(m_Dice1);
	drawObject(m_Dice2);

}

void Board::destroy()
{
	SDL_DestroyTexture(m_background);
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

int2 Board::roll()
{
	int2 dice;
	dice.x = rand() % 6 + 1;
	dice.y = rand() % 6 + 1;
	return dice;
}
}

void Board::loadDistricts()
{
	fstream stream;
	string tmp;

	stream.open(CONFIG_FOLDER + "districts.txt");

	while(!stream.eof())
	{
		stream >> tmp;

		District _district;

		_district.init(tmp);

		m_districts.push_back(_district);
	}
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
}

void Board::loadQuestions()
{
	fstream stream;
	string tmp;

	stream.open(CONFIG_FOLDER + "questions.txt");

	while (!stream.eof())
	{
		stream >> tmp;

		Question _question;

		_question.init(tmp);

		m_questions.push_back(_question);
	}
}

Question Board::drawQuestion()
{
	int random = rand() % m_questions.size();	

	return m_questions[random];
}
