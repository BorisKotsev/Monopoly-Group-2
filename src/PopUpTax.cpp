#include "PopUpTax.h"
#include "InputManager.h"
#include "Board.h"

PopUpTax::PopUpTax()
{
}

PopUpTax::~PopUpTax()
{
}

void PopUpTax::init(int argTaxPrice)
{


	string tmp, img;
	taxPrice = argTaxPrice;

	fstream stream;
	stream.open(CONFIG_FOLDER + "PopUpTax.txt");
	stream >> tmp >> img;
	stream >> tmp >> m_popUp.rect.x >> m_popUp.rect.y >> m_popUp.rect.w >> m_popUp.rect.h;
	stream >> tmp >> okButton.x >> okButton.y >> okButton.w >> okButton.h;
	stream.close();


	m_popUp.texture = loadTexture(img);

	m_TaxPrice.init("TaxPrice.txt");

	m_TaxPrice.setText(to_string(taxPrice));

	okPressed = false;

	//cout << "text" <<  << endl;
}

void PopUpTax::draw()
{
	drawObject(m_popUp);
	m_TaxPrice.update();
	m_TaxPrice.draw();
}

void PopUpTax::Ok()
{
	if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, okButton))
	{
		okPressed = true;
	}
	//cout << okButton.x << " " << okButton.y << endl;
}

void PopUpTax::destroy()
{
	SDL_DestroyTexture(m_popUp.texture);
	m_TaxPrice.destroy();
}

int PopUpTax::getPrice()
{
	return taxPrice;
}




