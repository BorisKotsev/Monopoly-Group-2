#pragma once

#include "Engine.h"
#include "District.h"
#include "Station.h"
#include "TextField.h"

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

	void addDistrict(District district,int playerTurn);
	void addStation(Station station, int playerTurn);

	void movePlayer(int2);
	void goToJail();

	void OwnedDistricts(int playerTurn);
	void destroyOwnedDistricts();

	vector<District> getDistrict();
	int currentmove = 0;
	int sideOfBoard = 0;
	int colorsOwned[8];
	int stationsOwned = 0;

	char m_player_location;
	bool jail;
	int jailTime;
	int player_number;
	int allColors[8]= { 3,4,5,6,7,8,9,10 };

	vector <District> m_districts;
	vector <Station> m_stations;
private:
	Drawable m_player;

	int m_money;

	vector<TextField> m_ownedDistricts;
	vector<TextField> m_ownedStations;

	
	int nextLine = 0; // related to addDistrict

};