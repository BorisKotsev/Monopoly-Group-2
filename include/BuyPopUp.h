#pragma once
#include "defines.h"
#include "TextField.h"
#include "Presenter.h"
class BuyPopUp
{
public:
	BuyPopUp();
	~BuyPopUp();

	void init(string name, int price);
	void draw();
	bool Buy();
	void destroy();
	bool isPressed;
	bool inIt=true;
private:
	Drawable m_popUp;
	TextField m_name;
	TextField m_price;
	SDL_Rect buttons[2];
};