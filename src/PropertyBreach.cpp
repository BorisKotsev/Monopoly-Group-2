#include "PropertyBreach.h"
#include "InputManager.h"
#include "Board.h"

PropertyBreach::PropertyBreach()
{
}

PropertyBreach::~PropertyBreach()
{
}

void PropertyBreach::init(int playerBreachNumber, int ownerNumber)
{
	string tmp, img;
	fstream stream;
	stream.open(CONFIG_FOLDER + "PropertyBreach.txt");
	stream >> tmp >> img;
	stream >> tmp >> m_popUp.rect.x >> m_popUp.rect.y >> m_popUp.rect.w >> m_popUp.rect.h;
	stream >> tmp >> okButton.x >> okButton.y >> okButton.w >> okButton.y;
	stream.close();

	m_popUp.texture = loadTexture(img);

	m_playerBreach.init("playerBreach.txt");

	m_playerBreach.setText(to_string(playerBreachNumber));

	m_owner.init("owner.txt");

	m_owner.setText(to_string(ownerNumber));


	okPressed = false;

}

void PropertyBreach::draw()
{
	drawObject(m_popUp);
	m_playerBreach.update();
	m_owner.update();
	m_playerBreach.draw();
	m_owner.draw();
}

void PropertyBreach::Ok()
{
	if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, okButton))
	{
		okPressed = true;
	}
}

void PropertyBreach::destroy()
{
	SDL_DestroyTexture(m_popUp.texture);
	m_playerBreach.destroy();
	SDL_DestroyTexture(m_popUp.texture);
	m_owner.destroy();
}
