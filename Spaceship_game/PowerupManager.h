#pragma once
#include "Powerup.h"
#include <vector>

class PowerupManager
{
public:
	bool createPowerup(float time, std::vector<std::shared_ptr<Powerup>>& powerups);
	void manageLifetime(std::vector<std::shared_ptr<Powerup>>& powerups);
	void updatePowerups(std::vector<std::shared_ptr<Powerup>>& powerups, SpaceshipPlayer* player);
	void renderPowerups(std::vector<std::shared_ptr<Powerup>>& powerups, sf::RenderTarget* target);
};

