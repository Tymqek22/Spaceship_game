#include "Asteroid.h"

#include <iostream>
#include <random>


std::mt19937 mt(std::random_device{}());

Asteroid::Asteroid(const sf::Texture& texture) : m_xDirection{ 0.f }, m_yDirection{ 0.f }, m_alive{ true }, m_texture { texture }
{
	m_asteroid.setTexture(m_texture);
	m_asteroid.setScale(0.3f, 0.3f);

	this->setPosition();
	this->setDirection();
	this->setBounds();
}

Asteroid::~Asteroid() {}

sf::Vector2f Asteroid::getPosition() const
{
	return m_asteroid.getPosition();
}

sf::Vector2f Asteroid::getSize() const
{
	float width = m_asteroid.getGlobalBounds().width;
	float height = m_asteroid.getGlobalBounds().height;

	return sf::Vector2f(width, height);
}

sf::FloatRect Asteroid::getAreaToCheck() const
{
	return sf::FloatRect(this->getPosition(), this->getSize());
}

float Asteroid::getTopBound() const
{
	return m_top;
}

float Asteroid::getBottomBound() const
{
	return m_bottom;
}

float Asteroid::getLeftBound() const
{
	return m_left;
}

float Asteroid::getRightBound() const
{
	return m_right;
}

bool Asteroid::getAliveStatus() const
{
	return m_alive;
}

void Asteroid::setBoost(float boost)
{
	if (m_xDirection > 0) {
		m_xDirection += boost;
	}
	else {
		m_xDirection -= boost;
	}

	if (m_yDirection > 0) {
		m_yDirection += boost;
	}
	else {
		m_yDirection -= boost;
	}
}

void Asteroid::setDirection()
{
	std::uniform_int_distribution<int> range{ -2,2 };
	do {
		m_xDirection = static_cast<float>(range(mt));
		m_yDirection = static_cast<float>(range(mt));
	} while ((m_xDirection == 0.f || m_yDirection == 0.f));
}

void Asteroid::setPosition()
{
	std::uniform_real_distribution<float> xRange{ 0.f,900.f };
	std::uniform_real_distribution<float> yRange{ 0.f,500.f };

	m_asteroid.setPosition(xRange(mt), yRange(mt));
}

void Asteroid::setBounds()
{
	m_top = m_asteroid.getGlobalBounds().top;
	m_bottom = m_asteroid.getGlobalBounds().top + m_asteroid.getGlobalBounds().height;
	m_left = m_asteroid.getGlobalBounds().left;
	m_right = m_asteroid.getGlobalBounds().left + m_asteroid.getGlobalBounds().width;
}

void Asteroid::bounce()
{
	if (m_top <= 0.f) {
		m_yDirection = -m_yDirection;
	}
	else if (m_bottom >= 800.f) {
		m_yDirection = -m_yDirection;
	}
	else if (m_left <= 0.f) {
		m_xDirection = -m_xDirection;
	}
	else if (m_right >= 1000.f) {
		m_xDirection = -m_xDirection;
	}
}

void Asteroid::hit()
{
	m_alive = false;
}

bool Asteroid::wallCollision()
{	
	if (m_top > 0.f && m_bottom < 800.f && m_left > 0.f && m_right < 1000.f) {
		return false;
	}
	else {
		this->bounce();
	}
	return false;
}

bool Asteroid::asteroidCollision(const sf::FloatRect& object)
{
	if (this->getAreaToCheck().intersects(object)) {
		return true;
	}

	return false;
}

void Asteroid::bounceFromAsteroid(Asteroid& asteroid)
{
	sf::FloatRect currentAsteroid(this->getPosition(), this->getSize());
	sf::FloatRect asteroidToCheck(asteroid.getPosition(), asteroid.getSize());

	if (currentAsteroid.intersects(asteroidToCheck) && this->getTopBound() <= asteroid.getBottomBound()) {
		m_yDirection = -m_yDirection;
	}
	else if (currentAsteroid.intersects(asteroidToCheck) && this->getBottomBound() >= asteroid.getTopBound()) {
		m_yDirection = -m_yDirection;
	}
}

void Asteroid::update()
{
	if (!this->wallCollision()) {
		m_asteroid.move(m_xDirection, m_yDirection);
		this->setBounds();
	}
}

void Asteroid::render(sf::RenderTarget* target)
{
	target->draw(m_asteroid);
}