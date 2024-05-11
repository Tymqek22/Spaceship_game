#include "SpaceshipPlayer.h"
#include "BulletManager.h"

#include <iostream>
#include <cmath>

SpaceshipPlayer::SpaceshipPlayer() 
	: SHOOTING_COOLDOWN{0.5f}, POWERUP_COOLDOWN{4.f}, m_points{0}, m_lowerScale{false}, m_powerupActive{false}, m_alive{true}
{
	if (!m_texture.loadFromFile("Textures/PlayerShip.png")) {
		std::cerr << "Error with opening a file.";
	}

	m_entity.setTexture(m_texture);
	m_entity.setScale(0.3f, 0.3f);
	m_entity.setPosition(480.f, 690.f);
}		

SpaceshipPlayer::~SpaceshipPlayer() {}

void SpaceshipPlayer::setCooldown(float cooldown)
{
	SHOOTING_COOLDOWN = cooldown;
}

void SpaceshipPlayer::setPowerupType(const PowerupType& powerup)
{
	m_currentPowerup = powerup;
}

void SpaceshipPlayer::setPowerupActivation(bool activated)
{
	m_powerupActive = activated;

	if (m_powerupActive) {

		m_powerupTimer.restart();
	}
}

void SpaceshipPlayer::setPoints(int points)
{
	m_points += points;
}

sf::Vector2f SpaceshipPlayer::getLeftWeaponPosition() const
{
	float leftPosition = m_entity.getGlobalBounds().left;
	float bottomPosition = m_entity.getGlobalBounds().top + m_entity.getGlobalBounds().height;

	return sf::Vector2f(leftPosition, bottomPosition);
}

sf::Vector2f SpaceshipPlayer::getRightWeaponPosition() const
{
	float rightPosition = m_entity.getGlobalBounds().left + m_entity.getGlobalBounds().width;
	float bottomPosition = m_entity.getGlobalBounds().top + m_entity.getGlobalBounds().height;

	return sf::Vector2f(rightPosition, bottomPosition);
}

int SpaceshipPlayer::getPoints() const
{
	return m_points;
}

float SpaceshipPlayer::getPowerupTimer() const
{
	sf::Time time = sf::seconds(4.f) - m_powerupTimer.getElapsedTime();

	return time.asSeconds();
}

bool SpaceshipPlayer::powerupActivated() const
{
	return m_powerupActive;
}

bool SpaceshipPlayer::isAlive() const
{
	return m_alive;
}

bool SpaceshipPlayer::hasAShield()
{
	if (this->powerupActivated() && m_currentPowerup == PowerupType::shield)
		return true;
	else
		return false;
}

void SpaceshipPlayer::shoot()
{
	if (m_powerupActive && m_currentPowerup == PowerupType::multishoot) {

		Bullet leftBullet(this->getLeftWeaponPosition());
		Bullet rightBullet(this->getRightWeaponPosition());

		m_bulletsShot.push_back(leftBullet);
		m_bulletsShot.push_back(rightBullet);
	}
	else {
		Bullet bullet(this->getWeaponPosition());

		m_bulletsShot.push_back(bullet);
	}
}

void SpaceshipPlayer::hit()
{
	m_alive = false;
	std::cout << "Player was hit!\n";
}

void SpaceshipPlayer::controlPowerup()
{
	switch (m_currentPowerup) {
		
	case PowerupType::reloadTime: {
		this->setCooldown(0.5f);
		m_powerupActive = false;
		break;
	}
	case PowerupType::shield: {
		m_powerupActive = false;
		break;
	}
	case PowerupType::multishoot: {
		m_powerupActive = false;
		break;
	}
	}
}

void SpaceshipPlayer::updateShip()
{
	sf::Time timer = m_clock.getElapsedTime();
	sf::Time powerupTimer = sf::seconds(POWERUP_COOLDOWN) - m_powerupTimer.getElapsedTime();

	//moving a ship left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		if (m_entity.getGlobalBounds().left > 0.f) {
			m_entity.move(-SHIP_SPEED, 0.f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		if (m_entity.getGlobalBounds().width + m_entity.getGlobalBounds().left < 1000.f) {
			m_entity.move(SHIP_SPEED, 0.f);
		}
		
	}
	
	//shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		
		if (timer.asSeconds() >= SHOOTING_COOLDOWN) {

			this->shoot();
			m_clock.restart();
		}
	}

	//powerup deactivating
	if (m_powerupActive && powerupTimer.asSeconds() <= 0.f) {

		this->controlPowerup();
	}
}

void SpaceshipPlayer::updateBullets(std::vector<Asteroid*>& asteroids)
{
	BulletManager manager;
	manager.manageLifetime(m_bulletsShot, asteroids);
	manager.eraseBullets(m_bulletsShot);
	manager.movePlayerBullets(m_bulletsShot);

	m_points += manager.getEarnedPoints();
}

void SpaceshipPlayer::updateBulletsWithEnemy(Spaceship* spaceship)
{
	BulletManager manager;
	manager.manageLifetimeSpaceship(m_bulletsShot, spaceship);
	manager.eraseBullets(m_bulletsShot);
	manager.movePlayerBullets(m_bulletsShot);
}