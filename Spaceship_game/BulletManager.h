#pragma once

#include "Bullet.h"
#include "Spaceship.h"

class BulletManager
{
private:
	int m_pointsEarned;

public:
	BulletManager();

	int getEarnedPoints() const;

	void eraseBullets(std::vector<Bullet>& bullets);
	void manageLifetime(std::vector<Bullet>& bullets, std::vector<Asteroid*>& asteroids);
	void manageLifetimeSpaceship(std::vector<Bullet>& bullets, Spaceship* spaceship);
	void renderBullets(std::vector<Bullet>& bullets, sf::RenderTarget* target);
	void movePlayerBullets(std::vector<Bullet>& bullets);
	void moveEnemyBullets(std::vector<Bullet>& bullets);
};

