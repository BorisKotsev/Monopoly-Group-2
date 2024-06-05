#include <random>
#include "Player.h"
#include "Presenter.h"

#define STARTX 1320
#define STARTY 900
#define CENTERYB 945
#define CENTERYT 55
#define CENTERXL 490
#define CENTERXR 1395


Player::Player()
{
}

Player::~Player()
{
}

void Player::init(string configFile, int arg_player_number)
{
    string tmp, textureImgPath;

    fstream stream;

    jailTime = 0;
    jail = false;
    stream.open(CONFIG_FOLDER + PLAYER_FOLDER + configFile);    
   stream >> tmp >> textureImgPath;

    stream.close();

    m_money = 1500;
    m_player.texture = loadTexture(textureImgPath);
    player_number = arg_player_number;
    
    switch (player_number)
    {
    case 1: m_player.rect.x = STARTX;
            m_player.rect.y = STARTY;
            break;

    case 2: m_player.rect.x = STARTX + 80;
            m_player.rect.y = STARTY;
            break;

    case 3: m_player.rect.x = STARTX;
            m_player.rect.y = STARTY + 80;
            break;

    case 4: m_player.rect.x = STARTX + 80;
            m_player.rect.y = STARTY + 80;
            
        default:
            break;
    }
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

int Player::checkMoney()
{
    return m_money;
}

void Player::addDistrict(District district,int playerTurn)
{
    m_districts.insert(m_districts.begin(), district);
    int color = district.getColor();
    ofstream file;

    file.open(CONFIG_FOLDER + FIELD_FOLDER + to_string(playerTurn) + "\\" + district.getName() + ".txt");
    file << "textrect: " << 1605 << " " << 185+nextLine*35<< " " << 35<<endl;
    file << "fontSize: " << 30<<endl;
    file << "textrect: " << 1605 << " " << 185 + nextLine * 35 << " " << 257 << " " << 35<<endl;
    file << "color: " << color<<endl;
    file << "backImg: ";
    file.close();
    
    for (int i = 0; i < 8; i++)
    {
        if (color == allColors[i])
        {
            colorsOwned[i] ++;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        cout << i << ":" << colorsOwned[i]<<endl;
    }
    nextLine++;
}

void Player::addStation(Station station, int playerTurn)
{
    m_stations.insert(m_stations.begin(), station);
    ofstream file;

    file.open(CONFIG_FOLDER + FIELD_FOLDER + to_string(playerTurn) + "\\" + station.getName() + ".txt");
    file << "textrect: " << 1605 << " " << 963 -  stationsOwned* 35 << " " << 35 << endl;
    file << "fontSize: " << 30 << endl;
    file << "textrect: " << 1605 << " " << 963 - stationsOwned * 35 << " " << 257 << " " << 35 << endl;
    file << "color: " << 1 << endl;
    file << "backImg: ";
    file.close();

    stationsOwned++;
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
            m_player.rect.y = CENTERYB;
            m_player.rect.x = STARTX - currentmove * 80;
            break;

        case 1: //Left
            m_player.rect.x = CENTERXL;
            m_player.rect.y = STARTY - currentmove * 80;
            break;

        case 2: //Up
            m_player.rect.y = CENTERYT;
            m_player.rect.x = 520 + currentmove * 80;
            break;

        case 3: //Right
            m_player.rect.x = CENTERXR;
            m_player.rect.y = 100 + currentmove * 80;
            break;
        default: break;

    }

   //cout << "side of board: " << sideOfBoard << " Current move: " << currentmove << " Dice results: " << diceResults << endl;
}

void Player::goToJail()
{
    jail = true;
    currentmove = 0;
    sideOfBoard = 1;
    m_player.rect.x = 510;
    m_player.rect.y = 940;
}

void Player::OwnedDistricts(int playerTurn)
{
    TextField tmp;
    for (int i = 0; i < m_districts.size(); i++)
    {
        tmp.init(to_string(playerTurn) +"\\" + m_districts[i].getName() + ".txt");
        tmp.setText(m_districts[i].getName());
        m_ownedDistricts.push_back(tmp);
    }
    for (int i = 0; i < m_stations.size(); i++)
    {
        tmp.init(to_string(playerTurn) +"\\" + m_stations[i].getName() + ".txt");
        tmp.setText(m_stations[i].getName());
        m_ownedStations.push_back(tmp);
    }
    for (int i = 0; i < m_ownedDistricts.size(); i++)
    {
        m_ownedDistricts[i].draw();
        m_ownedDistricts[i].update();
    }
    for (int i = 0; i < m_ownedStations.size(); i++)
    {
        m_ownedStations[i].draw();
        m_ownedStations[i].update();
    }
}

void Player::destroyOwnedDistricts()
{
    for (int i = 0; i < m_ownedDistricts.size(); i++)
    {
        m_ownedDistricts[i].destroy();
    }
    for (int i = 0; i < m_ownedStations.size(); i++)
    {
        m_ownedStations[i].destroy();
    }
}

vector<District> Player::getDistrict()
{
    return m_districts;
}

