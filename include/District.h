#pragma once

#include "Engine.h"
#include "Presenter.h"

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
	int getColor();
	string getName();
	void Bought(string name);
	void addHouses(int sideOfBoard);
	void drawHouse();

	bool m_canBeBought = true;
	DrawableWithRotation m_houses[5];

private:
	SDL_Rect m_district;

	string m_name;

	int numOfHouses;
	int m_color;
	int m_price;
	int m_electricity;
	int m_profit;
	int m_pollution;
	int houses;
	bool hotel;
};