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
    stream >> tmp >> m_electricity;
    stream >> tmp >> m_profit;
    stream >> tmp >> m_pollution;
    stream.close();

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
