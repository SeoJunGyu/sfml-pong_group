#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetScore(int score)
{
	this->score = score;
	static std::string formatScore = "SCORE: ";
	textScore.setString(formatScore + std::to_string(this->score));
	Utils::SetOrigin(textScore, Origins::TL);
}

void UiHud::SetScore1(int score)
{
	score1 = score;
	static std::string formatScore = "SCORE: ";
	textScore1.setString(formatScore + std::to_string(score1));
	Utils::SetOrigin(textScore1, Origins::TL);
}

void UiHud::SetScore2(int score)
{
	score2 = score;
	static std::string formatScore = "SCORE: ";
	textScore2.setString(formatScore + std::to_string(score2));
	Utils::SetOrigin(textScore2, Origins::TL);
}

void UiHud::SetMessage(const std::string& msg)
{
	textMessage.setString(msg);
	Utils::SetOrigin(textMessage, Origins::MC);
}

void UiHud::Init()
{
	fontId = "fonts/DS-DIGIT.ttf";

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	if (!isDuo)
	{
		textScore.setCharacterSize(90);
		textScore.setFillColor(sf::Color::White);
		textScore.setPosition(20, 20);

		textMessage.setCharacterSize(100);
		textMessage.setFillColor(sf::Color::Yellow);
		textMessage.setPosition(bounds.width * 0.5f, bounds.height * 0.5f);
	}
	else
	{
		textScore1.setCharacterSize(90);
		textScore1.setFillColor(sf::Color::White);
		textScore1.setPosition(20, 20);

		textScore2.setCharacterSize(90);
		textScore2.setFillColor(sf::Color::White);
		textScore2.setPosition(900.f, 20.f);

		textMessage.setCharacterSize(100);
		textMessage.setFillColor(sf::Color::Yellow);
		textMessage.setPosition(bounds.width * 0.5f, bounds.height * 0.5f);

		isWin = false;

		SetMessage("Press space to start!");
		SetScore1(0);
		SetScore2(0);
	}
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	if (!isDuo)
	{
		textScore.setFont(FONT_MGR.Get(fontId));
		textMessage.setFont(FONT_MGR.Get(fontId));
	}
	else
	{
		textScore1.setFont(FONT_MGR.Get(fontId));
		textScore2.setFont(FONT_MGR.Get(fontId));
		textMessage.setFont(FONT_MGR.Get(fontId));

		sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

		textScore1.setPosition(20, 20);
		textScore2.setPosition(900.f, 20.f);
		textMessage.setPosition(bounds.width * 0.5f, bounds.height * 0.5f);

		isShowMessage = true;
		SetMessage("Press space to start!");

		if (isWin)
		{
			SetScore1(0);
			SetScore2(0);
			isWin = false;
		}
	}
}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	if (!isDuo)
	{
		window.draw(textScore);
	}
	else
	{
		window.draw(textScore1);
		window.draw(textScore2);
	}

	if (isShowMessage)
	{
		window.draw(textMessage);
	}
}
