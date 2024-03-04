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
	loadQuestions();
}

void Board::update()
{
}

void Board::draw()
{
	drawObject(m_background);
	
	m_questions[0].run();

	if (m_questions[0].m_answer == 1)
	{
		cout << m_questions[0].getMoney() << endl;
		m_questions[0].m_answer = -1;
	}
	else if (m_questions[0].m_answer == 0)
	{
		cout << m_questions[0].getMoney() * m_questions[0].getPercent() / 100 << endl;
		m_questions[0].m_answer = -1;
	}
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
	int numQuestions = 1;

	for (int i = 1; i <= numQuestions; i++)
	{
		string tmp = "Question" + to_string(i) + ".txt";

		Question _question;

		_question.init(tmp);

		m_questions.push_back(_question);
	}
}
