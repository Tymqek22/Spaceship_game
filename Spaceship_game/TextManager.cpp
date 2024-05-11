#include "TextManager.h"

#include <sstream>
#include <iomanip>

void TextManager::createText()
{
	m_font.loadFromFile("Font/Retro_Gaming.ttf");

	m_score.setFont(m_font);
	m_powerupCountdown.setFont(m_font);

	m_score.setString("Score: 0");
	m_score.setFillColor(sf::Color::White);
	m_score.setPosition(10.f, 10.f);

	m_powerupCountdown.setFillColor(sf::Color::White);
	m_powerupCountdown.setPosition(10.f, 40.f);
}

void TextManager::updateText(int points)
{
	std::stringstream ss;
	ss << "Score: " << points;

	m_score.setString(ss.str());
}

void TextManager::updatePowerupText(float time)
{
	std::stringstream ss;

	ss << "Powerup: " <<std::fixed << std::setprecision(2) << time;

	m_powerupCountdown.setString(ss.str());
}

void TextManager::renderText(sf::RenderTarget* target)
{
	target->draw(m_score);
}

void TextManager::renderPowerupText(sf::RenderTarget* target)
{
	target->draw(m_powerupCountdown);
}