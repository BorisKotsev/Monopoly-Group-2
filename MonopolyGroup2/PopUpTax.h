#pragma once
#include <TextField.h>

#include <stdio.h>

class PopUpTax
{
public:
	PopUpTax();
	~PopUpTax();

	void init(string, int);
	void destroy();


private:

	string taxType;
	int taxPrice;
	TextField popUpField;

};
