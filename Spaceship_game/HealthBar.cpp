#include "HealthBar.h"

HealthBar::HealthBar() : m_dynamicBarLenght{ 78.f }
{
	m_baseBar.setSize(sf::Vector2f(80.f, 8.f));
	m_baseBar.setFillColor(sf::Color::White);

	m_dynamicBar.setSize(sf::Vector2f(78.f, 6.f));
	m_dynamicBar.setFillColor(sf::Color::Red);
}

void HealthBar::setXPosition(const sf::Vector2f& objectAxis)
{
	float left = objectAxis.x - 35.f;
	
	m_baseBar.setPosition(left, objectAxis.y);
	m_dynamicBar.setPosition(left + 1.f, objectAxis.y + 1.f);

}

void HealthBar::setYPosition(float yPos)
{
	m_baseBar.setPosition(m_baseBar.getPosition().x, yPos);
	m_dynamicBar.setPosition(m_dynamicBar.getPosition().x, yPos + 1.f);
}

void HealthBar::updateLenght(float currentHealth, float maxHealth)
{
	float percent = currentHealth / maxHealth;
	float lenght = percent * m_dynamicBarLenght;

	m_dynamicBar.setSize(sf::Vector2f(lenght, 6.f));
}

void HealthBar::update(const sf::Vector2f& movingVector, float currentHealth)
{
	this->updateLenght(currentHealth, 50.f);

	m_baseBar.move(movingVector);
	m_dynamicBar.move(movingVector);
}

void HealthBar::render(sf::RenderTarget* target)
{
	target->draw(m_baseBar);
	target->draw(m_dynamicBar);
}