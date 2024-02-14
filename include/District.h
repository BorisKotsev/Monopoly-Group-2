#pragma once

#include "Engine.h"

class District
{
public:
	District();
	~District();

	void init(string configFile);

	int getPrice();
	int getElectricity();
	int getProfit();
	int getPollution();

	bool m_canBeBought = true;

private:
	SDL_Rect m_district;

	string m_color;

	int m_price;
	int m_electricity;
	int m_profit;
	int m_pollution;
};