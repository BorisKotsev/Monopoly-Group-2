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
	void Buy();
	void destroy();
	bool m_pressedYes;
	bool m_pressedNo;
private:
	Drawable m_popUp;
	TextField m_name;
	TextField m_price;
	SDL_Rect buttons[2];
};