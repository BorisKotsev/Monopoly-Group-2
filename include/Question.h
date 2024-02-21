#pragma once

#include "Engine.h"

class Question
{
public:
	Question();
	~Question();

	void init(string configFile);
	void update();
	void draw();
	void destroy();

private:
	Drawable m_question;
	Drawable m_ReadyBtn;

	SDL_Rect m_yesBtn;
	SDL_Rect m_noBtn;

	int m_answer; // 1 - right, -1 - wrong
	int m_money;
	int m_percent; //if the question is hard, the percent is lower
};