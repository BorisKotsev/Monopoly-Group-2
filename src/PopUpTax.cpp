#include "PopUpTax.h"
#include "InputManager.h"
#include "Board.h"

PopUpTax::PopUpTax()
{
}

PopUpTax::~PopUpTax()
{
}

void PopUpTax::init(string name, int argTaxPrice)
{

	string tmp, img;
	taxPrice = argTaxPrice;

	fstream stream;
	stream.open(CONFIG_FOLDER + "PopUpTax.txt");
	stream >> tmp >> img;
	stream >> tmp >> m_popUp.rect.x >> m_popUp.rect.y >> m_popUp.rect.w >> m_popUp.rect.h;
	stream >> tmp >> okButton.x >> okButton.y >> okButton.w >> okButton.y;
	stream.close();


	m_popUp.texture = loadTexture(img);
	m_TaxName.init("TaxName.txt");
	m_TaxPrice.init("TaxPrice.txt");
	m_TaxName.setText(name);
	m_TaxPrice.setText(to_string(argTaxPrice));

	this->name = name;
	taxPrice = argTaxPrice;

	okPressed = false;

	cout << "Rect" << m_popUp.rect.w << endl;
}

void PopUpTax::draw()
{
	drawObject(m_popUp);
	m_TaxName.draw();
	m_TaxPrice.draw();
	m_TaxName.update();
	m_TaxPrice.update();
}

void PopUpTax::Ok()
{
	if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, okButton))
	{
		okPressed = true;
	}
}

void PopUpTax::destroy()
{
	SDL_DestroyTexture(m_popUp.texture);
	m_TaxName.destroy();
	m_TaxPrice.destroy();
}

int PopUpTax::getPrice()
{
	return taxPrice;
}




