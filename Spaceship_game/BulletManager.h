#pragma once

#include "Bullet.h"
#include "Spaceship.h"
#include "SpaceshipPlayer.h"

class BulletManager
{
public:
	BulletManager();

	void eraseBullets(std::vector<Bullet>& bullets);
	void manageLifetime(std::vector<Bullet>& bullets, std::vector<std::shared_ptr<Asteroid>>& asteroids, SpaceshipPlayer* spaceship);
	void manageLifetimeSpaceship(std::vector<Bullet>& bullets, Spaceship* spaceship);
	void renderBullets(std::vector<Bullet>& bullets, sf::RenderTarget* target);
	void movePlayerBullets(std::vector<Bullet>& bullets);
	void moveEnemyBullets(std::vector<Bullet>& bullets);
};

