#include "Button.h"
#include "World.h"
Button::Button()
{
}

Button::~Button()
{
}

void Button::init(string config,string folder)
{
	fstream stream;
	string tmp, Img;
	stream.open(CONFIG_FOLDER + BUTTON_FOLDER + config);
	stream >> tmp >> Img;
	stream >> tmp >> m_button.rect.x >> m_button.rect.y >> m_button.rect.w >>m_button.rect.h ;
	stream.close();
	m_button.texture = loadTexture(folder+Img);
}

void Button::draw()
{
	drawObject(m_button);
}

void Button::update()
{
	Increase();
}

void Button::destroy()
{
	SDL_DestroyTexture(m_button.texture);
}

void Button::Increase()
{
	if (isMouseInRect(InputManager::m_mouseCoor, m_button.rect))
	{
	    if (counter < maxIncrease)
	    {
		     m_button.rect.w += increasePerFrame*2;
		     m_button.rect.h += increasePerFrame*2;
		     m_button.rect.x -= increasePerFrame;
		     m_button.rect.y -= increasePerFrame;
		     counter += increasePerFrame;
	    }

	}
    else if (counter > 0)
	{
		    m_button.rect.x += increasePerFrame;
		    m_button.rect.y += increasePerFrame;
			m_button.rect.w -= increasePerFrame*2;
			m_button.rect.h -= increasePerFrame*2;
			counter -= increasePerFrame;
    }

}

bool Button::isPressed()
{
	if (InputManager::isMousePressed() && isMouseInRect(InputManager::m_mouseCoor, m_button.rect))
	{
		return true;
	}
	return false;
}

