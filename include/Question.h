#pragma once

#include "Engine.h"

class Question
{
public:
	Question();
	~Question();

	void init(string configFile);
	void run();
	void destroy();

	int getMoney();
	int loseMoney();

	int m_answer; //1 for yes, 0 for no

private:
	Drawable m_mainQuestion;

	SDL_Texture* m_question;
	SDL_Rect m_readyBtn;

	SDL_Texture* m_postQuestion;
	SDL_Rect m_yesBtn;
	SDL_Rect m_noBtn;

	int m_money;
	int m_percent; //if the question is hard, the percent is lower
};