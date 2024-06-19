#include "Board.h"
#include "Presenter.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "World.h"

extern World world;

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
	m_Exit.init("ExitButton.txt","");
	m_info.rect = {1491,111,362,956};
	m_info.texture = loadTexture("Info.bmp");

	loadDices();
	loadTurnUI();
	diceDoubles = 0;
}

void Board::update()
{
	if (m_Exit.isPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
		return;
	}
	m_playerTurn.update();
	m_Roll.update();
	m_Exit.update();
	m_playerTurn.setText(to_string(playerTurn+1));
	m_players[playerTurn].OwnedDistricts(playerTurn);
	if (m_Roll.isPressed())
	{

		m_players[playerTurn].destroyOwnedDistricts();

		if (m_BuyDistrict != nullptr)
		{
			m_BuyDistrict->destroy();
			delete m_BuyDistrict;
			m_BuyDistrict = nullptr;

		}
		if (m_BuyHouses != nullptr)
		{
			m_BuyHouses->destroy();
			delete m_BuyHouses;
			m_BuyHouses = nullptr;

		}
		if (m_BuyStation != nullptr)
		{
			m_BuyStation->destroy();
			delete m_BuyStation;
			m_BuyStation = nullptr;

		}
		if (m_PayYourTaxes != nullptr)
		{
			m_PayYourTaxes->destroy();
			delete m_PayYourTaxes;
			m_PayYourTaxes = nullptr;
		}
		if (m_BreachPopUp != nullptr) {

			m_BreachPopUp->destroy();
			delete m_BreachPopUp;
			m_BreachPopUp = nullptr;

		}
		if (m_tmpQuestion != nullptr) {

			m_tmpQuestion->destroy();
			delete m_tmpQuestion;
			m_tmpQuestion = nullptr;

		}

		diceValue.x = roll().x;
		diceValue.y = roll().y;
		drawDice(diceValue);
		if (m_players[playerTurn].jail == true && m_players[playerTurn].jailTime<3)
		{
			m_players[playerTurn].jailTime++;
			playerTurn++;
		}
		else if (m_players[playerTurn].jailTime >= 3)
		{
			m_players[playerTurn].jailTime = 0;
			m_players[playerTurn].jail = false;
		}
		bool tmp = false;
		if (m_players[playerTurn].jail == false)
		{

		playerPrev = playerTurn;
		m_players[playerTurn].movePlayer(diceValue);
		playerPosition(m_players[playerTurn]);
		tmp = true;
		}

		if (diceValue.x != diceValue.y)
		{
			diceDoubles = 0;
			playerTurn++;
		}
		else
		{
			m_players[playerTurn].jail = false;
			diceDoubles++;
			if (!tmp)
			{
				m_players[playerTurn].movePlayer(diceValue);
				playerPosition(m_players[playerTurn]);
			}
			
			if (diceDoubles >= 3)
			{
				m_players[playerTurn].goToJail();
				playerTurn++;
				diceDoubles = 0;
			}
			
		}
		

		if (playerTurn > playersAmount - 1)
			playerTurn = 0;

	//cout << m_players[0].currentmove<<" " << m_players[0].sideOfBoard << endl;
	}
	if (m_BuyDistrict != nullptr && !m_players[playerPrev].jail)
	{
		if (m_tmpDistrict.m_canBeBought)
		{
			m_BuyDistrict->draw();
			m_BuyDistrict->Buy();

			if (m_BuyDistrict->m_pressedYes)
			{
				m_players[playerPrev].addDistrict(m_tmpDistrict,playerPrev);
				m_players[playerPrev].removeMoney(m_tmpDistrict.getPrice());

				m_BuyDistrict->destroy();
				delete m_BuyDistrict;
				m_BuyDistrict = nullptr;
				for (int i = 0; i < m_districts.size()-1; i++)
				{
					m_districts[i].Bought(m_tmpDistrict.getName());
				}

			}
			if (m_BuyDistrict !=nullptr && m_BuyDistrict->m_pressedNo)
			{
				m_BuyDistrict->destroy();
				delete m_BuyDistrict;
				m_BuyDistrict = nullptr;
			}

		}

			
			
	}
	if (m_BuyHouses != nullptr && !m_players[playerPrev].jail)
	{
		if (m_players[playerPrev].colorsOwned[m_tmpDistrict.getColor() - 3] == 3)
		{
			m_BuyHouses->draw();
			m_BuyHouses->Buy();

			if (m_BuyHouses->m_pressedYes)
			{
				cout << "yes" << endl;
				for (int i = 0; i < m_players[playerPrev].m_districts.size(); i++)
				{
					if (m_players[playerPrev].m_districts[i].getName() == m_tmpDistrict.getName())
						m_players[playerPrev].m_districts[i].addHouses(m_players[playerPrev].sideOfBoard);
				}
				m_players[playerPrev].removeMoney((m_tmpDistrict.getPrice()*50)/100);

				m_BuyHouses->destroy();
				delete m_BuyHouses;
				m_BuyHouses = nullptr;

			}
			if (m_BuyHouses != nullptr && m_BuyHouses->m_pressedNo)
			{
				cout << "no" << endl;
				m_BuyHouses->destroy();
				delete m_BuyHouses;
				m_BuyHouses = nullptr;
			}

		}

	}
	if (m_BuyStation != nullptr && !m_players[playerPrev].jail)
	{
		if (m_tmpStation.m_canBeBought)
		{
			m_BuyStation->draw();
			m_BuyStation->Buy();
			if (m_BuyStation->m_pressedYes)
			{
				m_players[playerPrev].addStation(m_tmpStation,playerPrev);
				m_players[playerPrev].removeMoney(m_tmpStation.getPrice());

				m_BuyStation->destroy();
				delete m_BuyStation;
				m_BuyStation = nullptr;
				for (int i = 0; i < m_stations.size() - 1; i++)
				{
					m_stations[i].Bought(m_tmpStation.getName());
				}

			}
			if (m_BuyStation != nullptr && m_BuyStation->m_pressedNo)
			{
				m_BuyStation->destroy();
				delete m_BuyStation;
				m_BuyStation = nullptr;
			}
		}
	}
	if (m_PayYourTaxes != nullptr)
	{
		m_PayYourTaxes->draw();
		m_PayYourTaxes->Ok();
		if (m_PayYourTaxes->okPressed)
		{
			m_players[playerPrev].removeMoney(m_PayYourTaxes->getPrice());

			m_PayYourTaxes->destroy();
			delete m_PayYourTaxes;
			m_PayYourTaxes = nullptr;
		}
	}

	if (m_BreachPopUp != nullptr) 
	{
		m_BreachPopUp->draw();
		m_BreachPopUp->Ok();
		if (m_BreachPopUp->okPressed)
		{
			m_players[playerPrev].removeMoney(m_BreachPopUp->getPrice());

			m_BreachPopUp->destroy();
			delete m_BreachPopUp;
			m_BreachPopUp = nullptr;
		}
	}

	if (m_tmpQuestion != nullptr) {

		m_tmpQuestion->run();


		if (m_tmpQuestion->m_answer == 1)
		{
			m_players[playerPrev].addMoney(m_tmpQuestion->getMoney());
			m_questions.pop();
			m_questions.push(*m_tmpQuestion);

			m_tmpQuestion->destroy();
			delete m_tmpQuestion;
			m_tmpQuestion = nullptr;
		}

		else if (m_tmpQuestion->m_answer == 0)
		{
			m_players[playerPrev].removeMoney(m_tmpQuestion->loseMoney());
			m_questions.pop();
			m_questions.push(*m_tmpQuestion);

			m_tmpQuestion->destroy();
			delete m_tmpQuestion;
			m_tmpQuestion = nullptr;
		}



		//cout << m_tmpQuestion->m_answer << endl;
	}

	winnerCheck();
	if (playersAmount == 1) {
		m_winner = m_players[0].player_number;
		world.m_stateManager.changeGameState(GAME_STATE::WIN_SCREEN);
		return;
	}
}

void Board::draw()
{
	drawObject(m_background);
	//drawObject(m_info);
	m_Roll.draw();
	m_Exit.draw();
	drawObject(m_Dice1);
	drawObject(m_Dice2);
	drawObject(m_TurnUi);
	m_playerTurn.draw();

	for (int i = 0; i < m_players.size(); i++) {
		m_players[i].draw();
		for (int j = 0; j < m_players[i].m_districts.size(); j++)
		{
				m_players[i].m_districts[j].drawHouse();
		}
	}
	
}

void Board::destroy()
{
	SDL_DestroyTexture(m_background);
	SDL_DestroyTexture(m_Dice1.texture);
	SDL_DestroyTexture(m_Dice2.texture);
	SDL_DestroyTexture(m_TurnUi.texture);
	SDL_DestroyTexture(m_info.texture);
	m_Roll.destroy();
	m_Exit.destroy();
	m_playerTurn.destroy();

	string tmp;

	for (int i = 0; i < playersAmount; i++)
	{
		auto& districts = m_players[i].m_districts;
		if (!districts.empty())
		{
			for (int j = 0; j < districts.size();)
			{
				tmp = CONFIG_FOLDER + FIELD_FOLDER + to_string(i) + "\\" + districts[j].getName() + ".txt";

				int result = remove(tmp.c_str());

				if (result != 0)
				{
					perror("File deletion failed");
					++j;
				}
				else
				{
					districts.erase(districts.begin() + j); 
				}
				
				tmp.clear();
			}
		}

		auto& stations = m_players[i].m_stations;
		if (!stations.empty())
		{
			for (int j = 0; j < stations.size();)
			{
				tmp = CONFIG_FOLDER + FIELD_FOLDER + to_string(i) + "\\" + stations[j].getName() + ".txt";

				int result = remove(tmp.c_str());

				if (result != 0)
				{
					perror("File deletion failed");
					++j;
				}
				else
				{
					stations.erase(stations.begin() + j);
				}

				tmp.clear();
			}
		}
	}
}

void Board::drawDice(int2 diceValue)
{
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

void Board::playerPosition(Player& playerOnTurn)
{
	playerOnTurn.m_player_location = boardLayout[playerOnTurn.currentmove];


	int not_district = 0;
	int ownerOfDistrict = 0;
	int ownerOfStation = 0;

	for (int i = 0; i < playerOnTurn.currentmove; i++) { //tape
		if (boardLayout[i] != 'd') {
			not_district++;
		}
	}


	switch (playerOnTurn.m_player_location)
	{
		case 'd': //district
			m_tmpDistrict = m_districts[(playerOnTurn.sideOfBoard * 6) + playerOnTurn.currentmove - not_district];
			ownerOfDistrict = districtOwner(m_tmpDistrict.getName());
			//cout << "Owner of " << m_tmpDistrict.getName() << " " << ownerOfDistrict << endl;
			if (playerOnTurn.checkMoney() >= m_tmpDistrict.getPrice() && m_tmpDistrict.m_canBeBought)
			{
				m_BuyDistrict = new BuyPopUp();
				m_BuyDistrict->init(m_tmpDistrict.getName(), m_tmpDistrict.getPrice(),false);
			}
			if (playerOnTurn.colorsOwned[m_tmpDistrict.getColor()-3] == 3)
			{
				m_BuyHouses = new BuyPopUp();
				m_BuyHouses->init(m_tmpDistrict.getName(), (m_tmpDistrict.getPrice()*50)/100, true);
			}
			else if (!m_tmpDistrict.m_canBeBought && ownerOfDistrict != playerOnTurn.player_number) {
				m_BreachPopUp = new PropertyBreach();
				m_BreachPopUp->init(playerOnTurn.player_number, ownerOfDistrict, m_tmpDistrict.getProfit());
			}
			break;

		case 's': //station
			m_tmpStation = m_stations[playerOnTurn.sideOfBoard]; //station stepped on
			ownerOfStation = stationOwner(m_tmpStation.getName());

			if (playerOnTurn.checkMoney() >= m_tmpStation.getPrice() && !ownerOfStation)
			{
				m_BuyStation = new BuyPopUp();
				m_BuyStation->init(m_tmpStation.getName(), m_tmpStation.getPrice(),false);

			}
			else if (ownerOfStation && ownerOfStation != playerOnTurn.player_number) {
				m_BreachPopUp = new PropertyBreach();
				m_BreachPopUp->init(playerOnTurn.player_number, ownerOfStation, m_tmpStation.getProfit());
			}

			break;

		case 't': //tax

			switch (playerOnTurn.sideOfBoard)
			{
			case 0:
				
				taxToPay = playerOnTurn.calculateProfitTax();
				break;

			case 1:

				taxToPay = playerOnTurn.caluclatePollutionTax();
				break;

			case 2:

				taxToPay = playerOnTurn.caluclateParadiseTax();
				break;

			case 3:

				taxToPay = playerOnTurn.calculateElectricityTax();
				break;

			default:
				break;
			}

			if (playerOnTurn.checkMoney() >= taxToPay){
				m_PayYourTaxes = new PopUpTax;
				m_PayYourTaxes->init(taxToPay);
				//cout<< "Rect " << m_PayYourTaxes->m_popUp.rect.y << endl;
			}

			break;

		case 'q': //question

			if (!m_questions.empty()) {
				m_tmpQuestion = &m_questions.front();
			}
			else {
				cout << "No questions left" << endl;
			}

			break;

		case 'e': //edge
			if (playerOnTurn.currentmove == 0 && playerOnTurn.sideOfBoard == 3)
			{
				playerOnTurn.goToJail();
			}
			break;

		default:
			break;
	}

	//cout << "Player location: " << playerOnTurn.m_player_location << "Player on turn:" << playerOnTurn.player_number << endl;
}

int Board::districtOwner(string districtName)
{
	int owner = 0;
	for (int i = 0; i < playersAmount; i++) {
		for (int j = 0; j < m_players[i].m_districts.size(); j++) {
			if (m_players[i].m_districts[j].getName() == districtName) {
				owner = i + 1;
				break;
			}
		}
	}
	return owner;
}

int Board::stationOwner(string stationName)
{
	int owner = 0;
	for (int i = 0; i < playersAmount; i++) {
		for (int j = 0; j < m_players[i].m_stations.size(); j++) {
			if (m_players[i].m_stations[j].getName() == stationName) {
				owner = i + 1;
				break;
			}
		}
	}
	return owner;
}

int2 Board::roll()
{
	int2 dice;

	dice.x = rand() % 6 + 1;
	dice.y = rand() % 6 + 1;
	dice = { 1,0 };
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
		m_tmpQuestion = &m_questions.front();
		cout << m_tmpQuestion->getMoney() << endl;
		m_tmpQuestion->run();

		if (m_tmpQuestion->m_answer == 1)
		{
			playerOnTurn.addMoney(m_tmpQuestion->getMoney());
			m_questions.pop();
			m_questions.push(*m_tmpQuestion);
		}
		else if (m_questions.front().m_answer == 0)
		{
			playerOnTurn.removeMoney(m_tmpQuestion->loseMoney());
			m_questions.pop();
			m_questions.push(*m_tmpQuestion);
		}
	}
	else
	{
		cout << "No questions left" << endl;
	}

}

void Board::winnerCheck()
{
	for (int i = 0; i < playersAmount; i++) {
		if (m_players[i].checkMoney() <= 0) {
			m_players.erase(m_players.begin() + i);
			playersAmount--;
		}
	}
}
