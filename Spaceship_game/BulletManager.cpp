#include "BulletManager.h"

BulletManager::BulletManager() : m_pointsEarned{ 0 } {}

int BulletManager::getEarnedPoints() const
{
	return m_pointsEarned;
}

void BulletManager::eraseBullets(std::vector<Bullet>& bullets)
{
	for (int i = 0; i < bullets.size(); i++) {

		if (!bullets[i].getAliveStatus() || bullets[i].detectedCollision()) {

			bullets.erase(bullets.begin() + i);
		}
	}
}

void BulletManager::manageLifetime(std::vector<Bullet>& bullets, std::vector<Asteroid*>& asteroids)
{
	for (auto& bullet : bullets) {

		for (auto& asteroid : asteroids) {

			if (bullet.objectCollision(asteroid->getAreaToCheck())) {

				bullet.hit();
				asteroid->hit();
				m_pointsEarned++;
			}
		}
	}
}

void BulletManager::manageLifetimeSpaceship(std::vector<Bullet>& bullets, Spaceship* spaceship)
{
	for (auto& bullet : bullets) {

		if (bullet.objectCollision(spaceship->getAreaToCheck()) && !spaceship->hasAShield()) {

			bullet.hit();
			spaceship->hit();
		}
	}
}

void BulletManager::renderBullets(std::vector<Bullet>& bullets, sf::RenderTarget* target)
{
	for (auto& bullet : bullets) {

		bullet.render(target);
	}
}

void BulletManager::movePlayerBullets(std::vector<Bullet>& bullets)
{
	for (auto& bullet : bullets) {

		bullet.update();
	}
}

void BulletManager::moveEnemyBullets(std::vector<Bullet>& bullets)
{
	for (auto& bullet : bullets) {

		bullet.enemyUpdate();
	}
}