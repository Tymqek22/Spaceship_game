#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class TextManager
{
private:
	sf::Font m_font;
	sf::Text m_score;
	sf::Text m_powerupCountdown;

public:
	TextManager() = default;

	void createText();
	void updateText(int points);
	void updatePowerupText(float time);
	void renderText(sf::RenderTarget* target);
	void renderPowerupText(sf::RenderTarget* target);
};

