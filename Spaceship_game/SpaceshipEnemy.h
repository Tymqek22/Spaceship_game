#pragma once
#include "Spaceship.h"

class SpaceshipEnemy : public Spaceship
{
private:
	int m_healthPoints;
	bool m_alive;

	Spaceship* m_player;

public:
	SpaceshipEnemy();
	~SpaceshipEnemy();

	void setPlayerAsEnemy(Spaceship* enemy);

	bool isAlive() const;
	bool hasAShield() override;

	void shoot() override;
	void hit() override;

	void updateShip() override;
	void updateBullets();

};

