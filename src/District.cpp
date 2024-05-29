#include "District.h"

District::District()
{
}

District::~District()
{
}

void District::init(string configFile)
{
    fstream stream;
    string tmp;
    stream.open(CONFIG_FOLDER + DISTRICT_FOLDER +configFile);
    stream >> tmp >> m_name;
    stream >> tmp >> m_color;
    stream >> tmp >> m_district.x >> m_district.y >> m_district.w >> m_district.h;
    stream >> tmp >> m_price;
    stream >> tmp >> m_electricity;
    stream >> tmp >> m_profit;
    stream >> tmp >> m_pollution;
    stream.close();

}

int District::getPrice()
{
    return m_price;
}

int District::getElectricity()
{
    return m_electricity;
}

int District::getProfit()
{
    return m_profit;
}

int District::getPollution()
{
    return m_pollution;
}

string District::getName()
{
    return m_name;
}
int District::getColor()
{
    return m_color;
}

void District::Bought(string name)
{
    if (m_name == name)
        m_canBeBought = false;
}

void District::addHouses()
{
    if (houses < 3)
        houses++;
    else
        hotel = true;
}
