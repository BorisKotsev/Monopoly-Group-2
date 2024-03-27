#pragma once

#include "defines.h"

class Writer
{
public:
	Writer();
	~Writer();

	void init();

	pair<int2, SDL_Texture*> getText(string text, COLOR colorName, int fontSize);

private:
	map<int, TTF_Font*> m_font;
	map<COLOR, SDL_Color> m_colors;

	string m_fontLocation;
};