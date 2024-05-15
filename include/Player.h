#pragma once

#include "Engine.h"
#include "District.h"
#include "Station.h"

class Player
{
public:
	Player();
	~Player();

	void init(string configFile, int arg_player_number);
	void update();
	void draw();
	void destroy();

	int calculateElectricityTax();
	int calculateProfitTax();
	int caluclateParadiseTax();
	int caluclatePollutionTax();

	void addMoney(int money);
	void removeMoney(int money);
	int checkMoney();

	void addDistrict(District district);
	void addStation(Station station);

	void movePlayer(int2);
	void goToJail();

	int currentmove = 0;
	int sideOfBoard = 0;

	char m_player_location;
	bool jail;
	int jailTime;
	int player_number;

	vector <District> m_districts;
private:
	Drawable m_player;

	int m_money;

	vector <Station> m_stations;

};