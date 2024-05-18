#pragma once

#include "Bullet.h"
#include "Asteroid.h"
#include "Spaceship.h"

enum class PowerupType { reloadTime, shield, multishoot };

class SpaceshipPlayer : public Spaceship
{
private:
	float SHOOTING_COOLDOWN;
	float POWERUP_COOLDOWN;
	int m_points;
	bool m_lowerScale;
	bool m_powerupActive;
	bool m_alive;
	PowerupType m_currentPowerup;
	sf::Clock m_powerupTimer;

public:
	SpaceshipPlayer();
	~SpaceshipPlayer();

	void setCooldown(float cooldown);
	void setPowerupType(const PowerupType& powerup);
	void setPowerupActivation(bool activated);
	void setPoints(int points);

	sf::Vector2f getLeftWeaponPosition() const;
	sf::Vector2f getRightWeaponPosition() const;
	int getPoints();
	float getPowerupTimer() const;
	PowerupType getPowerupType() const;

	bool powerupActivated() const;
	bool isAlive() const;
	bool hasAShield() override;

	void shoot() override;
	void hit() override;

	void controlPowerup();
	void updateShip() override;
	void updateBulletsWithEnemy(Spaceship* spaceship);
	void updateBullets(std::vector<Asteroid*>& asteroids);
};

