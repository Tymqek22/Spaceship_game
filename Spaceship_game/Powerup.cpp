#include "Powerup.h"
#include "Globals.h"

sf::Vector2f Powerup::getPosition() const
{
	return m_powerup.getPosition();
}

sf::Vector2f Powerup::getSize() const
{
	return m_powerup.getSize();
}

sf::FloatRect Powerup::getAreaToCheck() const
{
	return sf::FloatRect(this->getPosition(), this->getSize());
}

bool Powerup::collision(const sf::FloatRect& object)
{
	if (object.intersects(this->getAreaToCheck())) {

		return true;
	}
	return false;
}

bool Powerup::hasGone()
{
	if (m_powerup.getGlobalBounds().top + m_powerup.getGlobalBounds().height >= SCREEN_HEIGHT) {
		return true;
	}
	else {
		return false;
	}
}

bool Powerup::alive()
{
	return m_alive;
}

void Powerup::update(SpaceshipPlayer* spaceship)
{
	if (this->collision(spaceship->getAreaToCheck())) {
		m_hostSpaceship = spaceship;
		m_alive = false;
		this->activate();
	}
	else if (this->hasGone()) {
		m_alive = false;
	}
	else {
		m_powerup.move(0.f, POWERUP_SPEED);
	}
}

void Powerup::render(sf::RenderTarget* target)
{
	target->draw(m_powerup);
}