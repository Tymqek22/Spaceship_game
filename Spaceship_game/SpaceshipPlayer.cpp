#include "SpaceshipPlayer.h"
#include "BulletManager.h"
#include "Globals.h"

#include <iostream>

SpaceshipPlayer::SpaceshipPlayer() 
	: m_points{0}, m_shootingCooldown{PLAYERSHOOTING_COOLDOWN}, m_lowerScale{false}, m_powerupActive{false}, m_alive{true}
{
	if (!m_texture.loadFromFile("Textures/PlayerShip.png")) {
		std::cerr << "Error with opening a file.";
	}

	m_healthPoints = PLAYER_HEALTH;
	m_entity.setTexture(m_texture);
	m_entity.setScale(0.3f, 0.3f);
	m_entity.setPosition(480.f, 670.f);
	m_healthBar.setXPosition(this->getCenterPosition());
	m_healthBar.setYPosition(780.f);
}		

SpaceshipPlayer::~SpaceshipPlayer() {}

void SpaceshipPlayer::setCooldown(float cooldown)
{
	m_shootingCooldown = cooldown;
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

void SpaceshipPlayer::increasePoints(int points)
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

int SpaceshipPlayer::getPoints()
{
	return m_points;
}

float SpaceshipPlayer::getPowerupTimer() const
{
	sf::Time time = sf::seconds(POWERUP_COOLDOWN) - m_powerupTimer.getElapsedTime();

	return time.asSeconds();
}

PowerupType SpaceshipPlayer::getPowerupType() const
{
	return m_currentPowerup;
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
		Bullet bullet(this->getCenterPosition());

		m_bulletsShot.push_back(bullet);
	}
}

void SpaceshipPlayer::hit()
{
	m_healthPoints -= 10;

	if (m_healthPoints == 0) {
		m_alive = false;
	}
	std::cout << "Player was hit!\n";
}

void SpaceshipPlayer::deactivatePowerup()
{
	switch (m_currentPowerup) {
		
	case PowerupType::reloadTime: {
		this->setCooldown(PLAYERSHOOTING_COOLDOWN);
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

			m_entity.move(-PLAYER_SPEED, 0.f);
			m_healthBar.update(sf::Vector2f(-PLAYER_SPEED, 0.f), this->getHealth(), PLAYER_HEALTH);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		if (m_entity.getGlobalBounds().width + m_entity.getGlobalBounds().left < SCREEN_WIDTH) {

			m_entity.move(PLAYER_SPEED, 0.f);
			m_healthBar.update(sf::Vector2f(PLAYER_SPEED, 0.f), this->getHealth(), PLAYER_HEALTH);
		}
		
	}
	
	//shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		
		if (timer.asSeconds() >= m_shootingCooldown) {

			this->shoot();
			m_clock.restart();
		}
	}

	//powerup deactivating
	if (m_powerupActive && powerupTimer.asSeconds() <= 0.f) {

		this->deactivatePowerup();
	}

	m_healthBar.updateLenght(this->getHealth(), PLAYER_HEALTH);
}

void SpaceshipPlayer::updateBullets(std::vector<Asteroid*>& asteroids)
{
	BulletManager manager;
	manager.manageLifetime(m_bulletsShot, asteroids, this);
	manager.eraseBullets(m_bulletsShot);
	manager.movePlayerBullets(m_bulletsShot);
}

void SpaceshipPlayer::updateBulletsWithEnemy(Spaceship* spaceship)
{
	BulletManager manager;
	manager.manageLifetimeSpaceship(m_bulletsShot, spaceship);
	manager.eraseBullets(m_bulletsShot);
	manager.movePlayerBullets(m_bulletsShot);
}