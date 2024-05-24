#include "SpaceshipEnemy.h"
#include "BulletManager.h"
#include "Globals.h"

#include <iostream>

SpaceshipEnemy::SpaceshipEnemy() : m_alive{true}, m_player{nullptr}
{
	if (!m_texture.loadFromFile("Textures/Enemy.png")) {
		std::cerr << "Error with opening a file.";
	}

	m_healthPoints = ENEMY_HEALTH;
	m_entity.setTexture(m_texture);
	m_entity.setScale(0.1f, 0.1f);
	m_entity.setPosition(480.f, 30.f);
	m_healthBar.setXPosition(this->getWeaponPosition());
	m_healthBar.setYPosition(5.f);
}

SpaceshipEnemy::~SpaceshipEnemy() {}

void SpaceshipEnemy::setPlayerAsEnemy(Spaceship* enemy)
{
	m_player = enemy;
}

bool SpaceshipEnemy::isAlive() const
{
	return m_alive;
}

bool SpaceshipEnemy::hasAShield()
{
	return false;
}

void SpaceshipEnemy::shoot()
{
	Bullet bullet(this->getWeaponPosition());

	m_bulletsShot.push_back(bullet);
}

void SpaceshipEnemy::hit()
{
	m_healthPoints -= 10;

	if (m_healthPoints == 0) {

		m_alive = false;
	}
	std::cout << "Enemy health: " << m_healthPoints << '\n';
}

void SpaceshipEnemy::updateShip()
{
	sf::Time timer = m_clock.getElapsedTime();

	if (m_player->getWeaponPosition().x > m_entity.getGlobalBounds().left + m_entity.getGlobalBounds().width) {
		m_entity.move(ENEMY_SPEED, 0.f);
		m_healthBar.update(sf::Vector2f(ENEMY_SPEED, 0.f), this->getHealth(), ENEMY_HEALTH);
	}
	else if (m_player->getWeaponPosition().x < m_entity.getGlobalBounds().left) {
		m_entity.move(-ENEMY_SPEED, 0.f);
		m_healthBar.update(sf::Vector2f(-ENEMY_SPEED, 0.f), this->getHealth(), ENEMY_HEALTH);
	}

	if (timer.asSeconds() >= ENEMYSHOOTING_COOLDOWN) {

		this->shoot();
		m_clock.restart();
	}

	m_healthBar.updateLenght(this->getHealth(), ENEMY_HEALTH);
}

void SpaceshipEnemy::updateBullets()
{
	BulletManager manager;
	manager.manageLifetimeSpaceship(m_bulletsShot, m_player);
	manager.eraseBullets(m_bulletsShot);
	manager.moveEnemyBullets(m_bulletsShot);
}