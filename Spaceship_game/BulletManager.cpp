#include "BulletManager.h"
#include <algorithm>

BulletManager::BulletManager() {}

void BulletManager::eraseBullets(std::vector<Bullet>& bullets)
{
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& bullet) 
		{
			if (!bullet.getAliveStatus() || bullet.wallCollision()) {
				return true;
			}
			else
				return false;
		}), bullets.end());
}

void BulletManager::manageLifetime(std::vector<Bullet>& bullets, std::vector<Asteroid*>& asteroids, SpaceshipPlayer* player)
{
	for (auto& bullet : bullets) {

		for (auto& asteroid : asteroids) {

			if (bullet.objectCollision(asteroid->getAreaToCheck())) {

				bullet.hit();
				asteroid->hit();
				player->increasePoints(1);
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