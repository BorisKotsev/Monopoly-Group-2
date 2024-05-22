#pragma once
#include "TextField.h"

class PropertyBreach {
public:

	PropertyBreach();
	~PropertyBreach();

	void init(int, int);
	void draw();
	void Ok();
	void destroy();

	bool okPressed;


private:

	string name;
	Drawable m_popUp;
	TextField m_playerBreach;
	TextField m_owner;
	SDL_Rect okButton;
};