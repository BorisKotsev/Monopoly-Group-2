#include <random>
#include "Player.h"
#include "Presenter.h"

#define STARTX 1320
#define STARTY 900


Player::Player()
{
}

Player::~Player()
{
}

void Player::init(string configFile)
{
    string tmp, textureImgPath;

    fstream stream;

    stream.open(CONFIG_FOLDER + PLAYER_FOLDER + configFile);    
   stream >> tmp >> textureImgPath;

    stream.close();

    m_money = 1500;
    m_player.texture = loadTexture(textureImgPath);
    m_player.rect.x = STARTX;
    m_player.rect.y = STARTY;
    m_player.rect.w = 50;
    m_player.rect.h = 50;
}

void Player::update()
{

}

void Player::draw()
{
    drawObject(m_player);
}

void Player::destroy()
{
    SDL_DestroyTexture(m_player.texture);
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
    int currentParadiseTax;

    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<>dis(100, 150);

    currentParadiseTax = dis(gen);

    return currentParadiseTax;
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

void Player::movePlayer(int2 argRolledDice)
{

    int diceResults = argRolledDice.x + argRolledDice.y;

    currentmove += diceResults;

    if (currentmove / 10 >= 1 && sideOfBoard != 3) {
        sideOfBoard += 1;
        currentmove = currentmove - (10 * (currentmove / 10));
        diceResults = diceResults - (10 * (currentmove / 10));
    }
    else if (currentmove / 10 >= 1 && sideOfBoard == 3) {
        sideOfBoard = 0;
        currentmove = currentmove - (10 * (currentmove / 10));
        diceResults = diceResults - (10 * (currentmove / 10));
    }

    switch (sideOfBoard) {
        case 0: //Down
            m_player.rect.y = 900;
            m_player.rect.x = STARTX - currentmove * 80;
            break;

        case 1: //Left
            m_player.rect.x = 440;
            m_player.rect.y = STARTY - currentmove * 80;
            break;

        case 2: //Up
            m_player.rect.y = 20;
            m_player.rect.x = 440 + currentmove * 80;
            break;

        case 3: //Right
            m_player.rect.x = 1320;
            m_player.rect.y = 20 + currentmove * 80;
            break;
        default: break;

    }

  //cout << "side of board: " << sideOfBoard << " Current move: " << currentmove << " Dice results: " << diceResults << endl;
}

