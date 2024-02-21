#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::init(string configFile)
{
    string tmp;

    fstream stream;

    stream.open(CONFIG_FOLDER + configFile);
    stream >> tmp >> textureImgPath;

    stream.close();

}

void Player::update()
{
}

void Player::draw()
{
   
}

void Player::destroy()
{
}

int Player::calculateElectricityTax()
{
    int currentElectrictyTax = 0;


    //Electricity Tax for districts
    for (int i = 0; i < m_districts.size(); i++) {
        currentElectrictyTax += m_districts[i].getElectricity();
    }

    //Electricity Tax for metro stations
    for (int i = 0; i < m_stations.size(); i++) {
        currentElectrictyTax += m_stations[i].getElectricity();
    }

    return currentElectrictyTax;
}

int Player::calculateProfitTax()
{
    int currentProfitTax = 0;


    //Profit Tax for districts
    for (int i = 0; i < m_districts.size(); i++) {
        currentProfitTax += m_districts[i].getProfit();
    }

    //Profit Tax for metro stations
    for (int i = 0; i < m_stations.size(); i++) {
        currentProfitTax += m_stations[i].getProfit();
    }

    return currentProfitTax;
}

int Player::caluclateParadiseTax()
{
    return 0;
}

int Player::caluclatePollutionTax()
{
    int currentPollutionTax = 0;


    //Pollution Tax for districts
    for (int i = 0; i < m_districts.size(); i++) {
        currentPollutionTax += m_districts[i].getPollution();
    }

    //Pollution Tax for metro stations
    for (int i = 0; i < m_stations.size(); i++) {
        currentPollutionTax += m_stations[i].getPollution();
    }

    return currentPollutionTax;

    return 0;
}

void Player::addMoney(int money)
{
    m_money += money;
}

void Player::removeMoney(int money)
{
    m_money -= money;
}

void Player::addDistrict(District district)
{
    m_districts.insert(m_districts.begin(), district);
}

void Player::addStation(Station station)
{
    m_stations.insert(m_stations.begin(), station);
}

