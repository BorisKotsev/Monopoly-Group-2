#pragma once

#include "Engine.h"

class Station
{
public:
	Station();
	~Station();

	void init(string configFile);

	int getPrice();
	int getElectricity();
	int getProfit();
	int getPollution();

	bool m_canBeBought = true;

private:
	SDL_Rect m_station;

	string m_name;

	int m_price;
	int m_electricity;
	int m_profit;
	int m_pollution;
};