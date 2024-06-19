#pragma once
#include "TextField.h"

class PropertyBreach {
public:

	PropertyBreach();
	~PropertyBreach();

	void init(int, int, int);
	void draw();
	void Ok();
	void destroy();
	int getPrice();

	bool okPressed;


private:

	string name;
	Drawable m_popUp;
	TextField m_playerBreach;
	TextField m_owner;
	TextField m_rent;
	int m_rentPrice;
	SDL_Rect okButton;
};