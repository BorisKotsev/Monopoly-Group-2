#pragma once

#include "Writer.h"

class TextField
{
public:
	TextField();
	~TextField();

	void init(string configFile);

	void update();
	void draw();
	void destroy();

	void setText(string text);


	bool m_needToDraw;

private:
	string m_value;
	Drawable m_text;
	Drawable m_background;

	int m_fontSize;
	int m_color;
};