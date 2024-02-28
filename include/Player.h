#pragma once

#include "Engine.h"
#include "District.h"
#include "Station.h"

class Player
{
public:
	Player();
	~Player();

	void init(string configFile);
	void update();
	void draw();
	void destroy();

	int calculateElectricityTax();
	int calculateProfitTax();
	int caluclateParadiseTax();
	int caluclatePollutionTax();

	void addMoney(int money);
	void removeMoney(int money);

	void addDistrict(District district);
	void addStation(Station station);

	void movePlayer(int2);

private:
	Drawable m_player;

	int m_money;

	vector <District> m_districts;
	vector <Station> m_stations;

};