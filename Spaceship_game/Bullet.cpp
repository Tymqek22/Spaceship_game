#include "Bullet.h"
#include "Spaceship.h"

Bullet::Bullet(const sf::Vector2f& startPos) : m_startPosition{ startPos }
{
	m_bullet.setSize(sf::Vector2f(10.f, 10.f));
	m_bullet.setFillColor(sf::Color::Green);
	m_bullet.setPosition(m_startPosition);
	m_alive = true;
}

Bullet::~Bullet() {}

sf::Vector2f Bullet::getPosition() const
{
	return m_bullet.getPosition();
}

sf::Vector2f Bullet::getSize() const
{
	return m_bullet.getSize();
}

bool Bullet::getAliveStatus() const
{
	return m_alive;
}

void Bullet::hit()
{
	m_alive = false;
}

bool Bullet::detectedCollision()
{
	if (m_bullet.getGlobalBounds().top <= 0.f) {
		return true;
	}
	else if (m_bullet.getGlobalBounds().top + m_bullet.getGlobalBounds().height >= 800.f) {
		return true;
	}
	return false;
}

bool Bullet::objectCollision(const sf::FloatRect& area)
{
	sf::FloatRect bulletToCheck(this->getPosition(), this->getSize());

	if (area.intersects(bulletToCheck)) {
		return true;
	}
	return false;
}

void Bullet::update()
{
	m_bullet.move(0.f, -BULLET_SPEED);
}

void Bullet::enemyUpdate()
{
	m_bullet.move(0.f, BULLET_SPEED);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(m_bullet);
}
