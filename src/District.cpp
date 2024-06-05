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
    stream.close();

    numOfHouses = 5;
    houses = 0;

    m_profit = m_price / 10;
    m_electricity = m_price / 20;
    m_pollution = m_price / 25;
    for (int i = 0; i < numOfHouses; i++)
    {
        m_houses[i].texture = loadTexture("House.bmp");
        m_houses[i].rect ={-20,-20,20,20};
    }
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

void District::addHouses(int sideOfBoard)
{
    if (houses < numOfHouses)
    {
        houses++;
        cout << houses << endl;
    }
    else
        hotel = true;
    cout << "houses on district" << houses << endl;

    switch (sideOfBoard)
    {
    case 0: //Down
        m_houses[houses].rect.x = (m_district.x + 5)*houses;
        m_houses[houses].rect.y = m_district.y + 5;
        //cout << "x = " << m_houses[houses].rect.x << " y = " << m_houses[houses].rect.y << endl;
        //cout << "w = " << m_houses[houses].rect.w << " h = " << m_houses[houses].rect.h << endl;
        break;

    case 1: //Left
        m_houses[houses].angle = 90;
        m_houses[houses].rect.x = m_district.x + 80 + 5;
        m_houses[houses].rect.y = (m_district.y + 5)*houses;
        break;

    case 2: //Up
        m_houses[houses].angle = 180;
        m_houses[houses].rect.x = (m_district.x + 5) * houses;
        m_houses[houses].rect.y = m_district.y + 80 + 5;
        break;

    case 3: //Right
        m_houses[houses].angle = 270;
        m_houses[houses].rect.x = m_district.x + 5;
        m_houses[houses].rect.y = (m_district.y + 5) * houses;
        break;

    }

    m_profit += houses*5;
}

void District::drawHouse()
{
    for (int i = 0; i < numOfHouses; i++)
    {
        cout << "x = " << m_houses[i].rect.x << " y = " << m_houses[i].rect.y;
        cout << " w = " << m_houses[i].rect.w << " h = " << m_houses[i].rect.h << endl;
        if (m_houses[i].rect.x != -20 || m_houses[i].rect.y != -20)
        {
            drawObject(m_houses[i]);
        }
    }
}
