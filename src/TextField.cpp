#include "TextField.h"
#include "Presenter.h"

TextField::TextField()
{
}

TextField::~TextField()
{
}

void TextField::init(string configFile)
{
	configFile = CONFIG_FOLDER + FIELD_FOLDER + configFile;


	string tmp, background;

	fstream stream;
	stream.open(configFile);

	stream >> tmp >> m_text.rect.x >> m_text.rect.y >> m_text.rect.h;
	stream >> tmp >> m_fontSize;
	stream >> tmp >> m_background.rect.x >> m_background.rect.y >> m_background.rect.w >> m_background.rect.h;
	stream >> tmp >> m_color;
	stream >> tmp >> background;

	stream.close();

	m_background.texture = loadTexture(FIELD_FOLDER + background);

	m_needToDraw = false;
	m_needToDrawAll = true;
}

void TextField::update()
{
	if (m_value.length() > 0 && m_needToDrawAll)
	{
		auto value = Presenter::m_writer->getText(m_value, (COLOR)m_color, m_fontSize);

		if (m_text.texture != nullptr)
		{
			SDL_DestroyTexture(m_text.texture);
		}

		m_text.texture = value.second;
		m_text.rect.w = value.first.x;
		m_text.rect.h = value.first.y;
	}

	cout << m_value << endl;
}

void TextField::draw()
{
	if (m_needToDrawAll)
	{

		if (m_needToDraw)
		{
			drawObject(m_background);
		}

		if (m_value.length() > 0)
		{
			drawObject(m_text);
		}
	}
}

void TextField::destroy()
{
	SDL_DestroyTexture(m_background.texture);
	SDL_DestroyTexture(m_text.texture);
	m_value.clear();
}

void TextField::setRect(int2 cord)
{
	m_text.rect.x = cord.x;
	m_text.rect.y = cord.y;
	m_background.rect.x = cord.x;
	m_background.rect.y = cord.y;
}


void TextField::setText(string text)
{
	if (m_value != text)
	{
		auto res = Presenter::m_writer->getText(text, (COLOR)m_color, m_fontSize);

		m_text.rect.x = m_background.rect.x + (m_background.rect.w - res.first.x) / 2;
		m_text.rect.y = m_background.rect.y + (m_background.rect.h - res.first.y) / 2;
		m_text.rect.w = res.first.x;
		m_text.rect.h = res.first.y;

		m_text.texture = res.second;

		m_value = text;
	}
}
