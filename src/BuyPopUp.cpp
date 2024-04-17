#include "BuyPopUp.h"
#include "InputManager.h"
#include "Board.h"
BuyPopUp::BuyPopUp()
{
}

BuyPopUp::~BuyPopUp()
{
}

void BuyPopUp::init(string name, int price)
{
	fstream stream;
	string tmp,Img;
	stream.open(CONFIG_FOLDER + "Buy.txt");
	stream >> tmp >> Img;
	stream >> tmp >> m_popUp.rect.x >> m_popUp.rect.y >> m_popUp.rect.w >> m_popUp.rect.h;
	stream >> tmp >> buttons[0].x >> buttons[0].y >> buttons[0].w >> buttons[0].h;
	stream >> tmp >> buttons[1].x >> buttons[1].y >> buttons[1].w >> buttons[1].h;
	stream.close();

	m_popUp.texture = loadTexture(Img);
	m_name.init("DistrictName.txt");
	m_price.init("Price.txt");
	m_name.setText(name);
	m_price.setText(to_string(price));
	
	

	isPressed = false;
	inIt = false;
}

void BuyPopUp::draw()
{
	drawObject(m_popUp);
	m_name.draw();
	m_price.draw();
	m_name.update();
	m_price.update();
}

bool BuyPopUp::Buy()
{

	if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, buttons[0]))
	{
		isPressed = true;
		return true;
	}
	else if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, buttons[1]))
	{
		isPressed = true;
		return false;
	}
}


void BuyPopUp::destroy()
{
	cout << "Why" << endl;
	SDL_DestroyTexture(m_popUp.texture);
	m_name.setText("");
	m_price.setText("");
	m_name.destroy();
	m_price.destroy();
}
