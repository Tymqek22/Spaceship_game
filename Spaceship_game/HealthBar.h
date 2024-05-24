#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
private:
	sf::RectangleShape m_baseBar;
	sf::RectangleShape m_dynamicBar;
	float m_dynamicBarLenght;

public:
	HealthBar();

	void setXPosition(const sf::Vector2f& objectAxis);
	void setYPosition(float yPos);
	void updateLenght(float currentHealth, float maxHealth);

	void update(const sf::Vector2f& move, float currentHealth, float maxHealth);
	void render(sf::RenderTarget* target);
};

