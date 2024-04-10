#include "PopUpTax.h"

PopUpTax::PopUpTax()
{
}

PopUpTax::~PopUpTax()
{
}

void PopUpTax::init(string taxConfigFile, int argTaxPrice)
{
	popUpField.init("popUpTax.txt");

	string tmp;

	fstream stream;
	stream.open(CONFIG_FOLDER + TAXES_FOLDER + taxConfigFile);


}
