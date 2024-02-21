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

	string backgorundImg, tmp;

	stream.open(CONFIG_FOLDER + configFile);

    stream >> tmp >> backgorundImg;

	stream.close();

	m_background = loadTexture(backgorundImg);

	//loadDistricts();
	//loadStations();
}

void Board::update()
{

}

void Board::draw()
{
	drawObject(m_background);
}

void Board::destroy()
{
	SDL_DestroyTexture(m_background);
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
