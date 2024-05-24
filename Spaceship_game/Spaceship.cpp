#include "Spaceship.h"
#include "BulletManager.h"

#include <iostream>

sf::Vector2f Spaceship::getWeaponPosition() const
{
	sf::Vector2f position;

	float center = ((m_entity.getGlobalBounds().width / 2) - 5.f) + m_entity.getGlobalBounds().left;
	float top = m_entity.getGlobalBounds().top;

	position.x = center;
	position.y = top;


	return position;
}

sf::Vector2f Spaceship::getPosition() const
{
	return m_entity.getPosition();
}

sf::Vector2f Spaceship::getSize() const
{
	float width = m_entity.getGlobalBounds().width;
	float height = m_entity.getGlobalBounds().height;

	return sf::Vector2f(width, height);
}

sf::FloatRect Spaceship::getAreaToCheck() const
{
	return sf::FloatRect(this->getPosition(), this->getSize());
}

float Spaceship::getHealth() const
{
	return m_healthPoints;
}

void Spaceship::renderShip(sf::RenderTarget* target, bool withHealthBar)
{
	target->draw(m_entity);

	if (withHealthBar) {
		m_healthBar.render(target);
	}
}

void Spaceship::renderBullets(sf::RenderTarget* target)
{
	BulletManager manager;
	manager.renderBullets(m_bulletsShot, target);
}