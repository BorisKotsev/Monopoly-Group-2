#pragma once
#include "TextField.h"

class PopUpTax
{
public:
	PopUpTax();
	~PopUpTax();

	void init(string, int);
	void draw();
	void Ok();
	void destroy();
	int getPrice();

	bool okPressed;


private:

	string taxType;
	Drawable m_popUp;
	int taxPrice;
	string name;
	TextField m_TaxName;
	TextField m_TaxPrice;
	SDL_Rect okButton;
};
