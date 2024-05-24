#include "PowerupReloadTime.h"
#include "Globals.h"
#include <random>

PowerupReloadTime::PowerupReloadTime() : Powerup()
{
	m_powerup.setFillColor(sf::Color::Red);
	m_powerup.setSize(POWERUP_SIZE);

	std::mt19937 mt(std::random_device{}());
	std::uniform_real_distribution<float> range{ 0.f,980.f };
	float xPosition = range(mt);
	m_powerup.setPosition(xPosition, 0.f);
}

PowerupReloadTime::~PowerupReloadTime() {}

void PowerupReloadTime::activate()
{
	m_hostSpaceship->setPowerupActivation(true);
	m_hostSpaceship->setPowerupType(PowerupType::reloadTime);
	m_hostSpaceship->setCooldown(0.2f);
}