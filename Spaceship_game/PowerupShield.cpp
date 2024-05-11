#include "PowerupShield.h"
#include <random>

PowerupShield::PowerupShield() : Powerup()
{
	m_powerup.setFillColor(sf::Color::Blue);
	m_powerup.setSize(sf::Vector2f(20.f, 20.f));

	std::mt19937 mt(std::random_device{}());
	std::uniform_real_distribution<float> range{ 0.f,980.f };
	float xPosition = range(mt);
	m_powerup.setPosition(xPosition, 0.f);
}

PowerupShield::~PowerupShield() {}

void PowerupShield::activate()
{
	m_hostSpaceship->setPowerupActivation(true);
	m_hostSpaceship->setPowerupType(PowerupType::shield);

}