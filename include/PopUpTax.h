#pragma once
#include "TextField.h"

class PopUpTax
{
public:
	PopUpTax();
	~PopUpTax();

	void init(int);
	void draw();
	void Ok();
	void destroy();
	int getPrice();

	bool okPressed;


private:

	string taxType;
	int taxPrice;
	string name;
	Drawable m_popUp;
	TextField m_TaxPrice;
	SDL_Rect okButton;
};
