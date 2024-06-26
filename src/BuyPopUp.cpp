#include "BuyPopUp.h"
#include "InputManager.h"
#include "Board.h"
BuyPopUp::BuyPopUp()
{
}

BuyPopUp::~BuyPopUp()
{
}

void BuyPopUp::init(string name, int price,bool buyHouse)
{
	fstream stream;
	string tmp,Img;
	stream.open(CONFIG_FOLDER + "Buy.txt");
	stream >> tmp >> Img;
	stream >> tmp >> m_popUp.rect.x >> m_popUp.rect.y >> m_popUp.rect.w >> m_popUp.rect.h;
	stream >> tmp >> buttons[0].x >> buttons[0].y >> buttons[0].w >> buttons[0].h;
	stream >> tmp >> buttons[1].x >> buttons[1].y >> buttons[1].w >> buttons[1].h;
	stream.close();

	if (buyHouse)
		Img = "buyHouse.bmp";
	m_popUp.texture = loadTexture(Img);
	m_name.init("DistrictName.txt");
	m_price.init("Price.txt");
	m_name.setText(name);
	m_price.setText(to_string(price));
	
	

	m_pressedYes = false;
	m_pressedNo = false;
}

void BuyPopUp::draw()
{
	drawObject(m_popUp);
	m_name.draw();
	m_price.draw();
	m_name.update();
	m_price.update();
}

void BuyPopUp::Buy()
{

	if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, buttons[0]))
	{
		m_pressedYes = true;
	}
	else if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, buttons[1]))
	{
	    m_pressedNo = true;
	}
}


void BuyPopUp::destroy()
{
	SDL_DestroyTexture(m_popUp.texture);
	m_name.destroy();
	m_price.destroy();
}
