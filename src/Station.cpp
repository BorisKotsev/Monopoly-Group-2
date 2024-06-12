#include "Station.h"

Station::Station()
{
}

Station::~Station()
{
}

void Station::init(string configFile)
{
    fstream stream;
    string tmp;
    stream.open(CONFIG_FOLDER+ STATION_FOLDER + configFile);
    stream >> tmp >> m_name;
    stream >> tmp >> m_station.x >> m_station.y >> m_station.w >> m_station.h;
    stream >> tmp >> m_price;
    stream.close();

    m_profit = m_price / 10;
    m_electricity = m_price / 20;
    m_pollution = m_price / 25;
}

int Station::getPrice()
{
    return m_price;
}

int Station::getElectricity()
{
    return m_electricity;
}

int Station::getProfit()
{
    return m_profit;
}

int Station::getPollution()
{
    return m_pollution;
}

void Station::Bought(string name)
{
    if (m_name == name)
        m_canBeBought = false;
}

string Station::getName()
{
    return m_name;
}
