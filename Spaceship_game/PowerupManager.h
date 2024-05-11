#pragma once
#include "Powerup.h"
#include <vector>

class PowerupManager
{
public:
	bool createPowerup(float time, std::vector<Powerup*>& powerups);
	void manageLifetime(std::vector<Powerup*>& powerups);
	void updatePowerups(std::vector<Powerup*>& powerups, SpaceshipPlayer* player);
	void renderPowerups(std::vector<Powerup*>& powerups, sf::RenderTarget* target);
};

