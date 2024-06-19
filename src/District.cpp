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
    hotel = false;

    m_profit = m_price / 10;
    m_electricity = m_price / 20;
    m_pollution = m_price / 25;
    for (int i = 0; i < numOfHouses; i++)
    {
        m_houses[i].texture = loadTexture("House.bmp");
        m_houses[i].rect ={-20,-20,18,18};
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
    if (houses < numOfHouses-1)
    {
        houses++;
    }
    else
        hotel = true;

    if(!hotel)
    { 
        switch (sideOfBoard)
        {
        case 0: //Down
            m_houses[houses].rect.x = (m_district.x + 2) + m_houses[houses].rect.w * (houses - 1);
            m_houses[houses].rect.y = m_district.y + 10;
            //cout << "x = " << m_houses[houses].rect.x << " y = " << m_houses[houses].rect.y << endl;
            //cout << "w = " << m_houses[houses].rect.w << " h = " << m_houses[houses].rect.h << endl;
            break;

        case 1: //Left
            m_houses[houses].angle = 90;
            m_houses[houses].rect.x = m_district.x + 120 + 10;
            m_houses[houses].rect.y = (m_district.y + 2) + m_houses[houses].rect.h * (houses - 1);
            break;

        case 2: //Up
            m_houses[houses].angle = 180;
            m_houses[houses].rect.x = (m_district.x + 2) + m_houses[houses].rect.w * (houses - 1);
            m_houses[houses].rect.y = m_district.y + 120 + 10;
            break;

        case 3: //Right
            m_houses[houses].angle = 270;
            m_houses[houses].rect.x = m_district.x + 10;
            m_houses[houses].rect.y = (m_district.y + 2) + m_houses[houses].rect.h * (houses - 1);
            break;

        }

    }
    else
    {
        m_houses[4].rect.w = 40;
        m_houses[4].rect.h = 40;
        switch (sideOfBoard)
        {
        case 0: //Down
            m_houses[4].rect.x = m_district.x + 20;
            m_houses[4].rect.y = m_district.y;
            break;

        case 1: //Left
            m_houses[4].angle = 90;
            m_houses[4].rect.x = m_district.x + 120;
            m_houses[4].rect.y = m_district.y + 20;
            break;

        case 2: //Up
            m_houses[4].angle = 180;
            m_houses[4].rect.x = m_district.x + 20;
            m_houses[4].rect.y = m_district.y + 120;
            break;

        case 3: //Right
            m_houses[4].angle = 270;
            m_houses[4].rect.x = m_district.x;
            m_houses[4].rect.y = m_district.y + 20;
            break;

        }
    }

    if (!hotel)
        m_profit += houses * 5;
    else
        m_profit += houses * 8;
}

void District::drawHouse()
{
    if (!hotel)
    {
        for (int i = 0; i < numOfHouses; i++)
        {
            if (m_houses[i].rect.x != -20 || m_houses[i].rect.y != -20)
            {
                drawObject(m_houses[i]);
            }
        }
    }
    else
    {
        for (int i = 0; i < numOfHouses-1; i++)
        {
                SDL_DestroyTexture(m_houses[i].texture);
        }
        drawObject(m_houses[4]);
    }
}
