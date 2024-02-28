#include "Question.h"
#include "Presenter.h"
#include "InputManager.h"

Question::Question()
{
}

Question::~Question()
{
}

void Question::init(string configFile)
{
	fstream stream;

	string tmp, questionImg, postQuestionImg;

	stream.open(CONFIG_FOLDER + QUESTION_FOLDER + configFile);

	stream >> tmp >> questionImg >> postQuestionImg;
	stream >> tmp >> m_money;
	stream >> tmp >> m_percent;

	stream.close();

	m_question = loadTexture(QUESTION_FOLDER + questionImg);
	m_postQuestion = loadTexture(QUESTION_FOLDER + postQuestionImg);
	
	m_mainQuestion.texture = m_question;
	m_mainQuestion.rect = {810, 450, 300, 180};

	m_readyBtn = { 1000, 570, 100, 50 };
	m_yesBtn = { 820, 560, 100, 60 };
	m_noBtn = { 1000, 560, 100, 60 };

	m_answer = -1;
}

void Question::run()
{
	drawObject(m_mainQuestion);

	if (m_mainQuestion.texture == m_postQuestion)
	{
		if (isMouseInRect(InputManager::m_mouseCoor, m_yesBtn) && InputManager::isMousePressed())
		{
			m_answer = 1;

			this->destroy();
		}
		else if (isMouseInRect(InputManager::m_mouseCoor, m_noBtn) && InputManager::isMousePressed())
		{
			m_answer = 0;

			this->destroy();
		}
	}

	if (m_mainQuestion.texture == m_question)
	{
		if (isMouseInRect(InputManager::m_mouseCoor, m_readyBtn) && InputManager::isMousePressed())
		{
			m_mainQuestion.texture = m_postQuestion;
		}
	}
}

void Question::destroy()
{
	SDL_DestroyTexture(m_mainQuestion.texture);
	SDL_DestroyTexture(m_question);
	SDL_DestroyTexture(m_postQuestion);
}

int Question::getMoney()
{
	return m_money;
}

int Question::getPercent()
{
	return m_percent;
}
