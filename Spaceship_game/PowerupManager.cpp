#include "PowerupManager.h"
#include "PowerupReloadTime.h"
#include "PowerupShield.h"
#include "PowerupMultishoot.h"
#include "Globals.h"
#include <random>
#include <algorithm>

bool PowerupManager::createPowerup(float time, std::vector<std::shared_ptr<Powerup>>& powerups)
{
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> powerupChoosing{ 1,3 };

	if (time >= POWERUP_TIMER) {

		int randomPowerup = powerupChoosing(mt);

		switch (randomPowerup) {
		case 1: {
			std::shared_ptr<Powerup> powerup = std::make_shared<PowerupReloadTime>();
			powerups.push_back(powerup);
			break;
		}
		case 2: {
			std::shared_ptr<Powerup> powerup = std::make_shared<PowerupShield>();
			powerups.push_back(powerup);
			break;
		}
		case 3: {
			std::shared_ptr<Powerup> powerup = std::make_shared<PowerupMultishoot>();
			powerups.push_back(powerup);
			break;
		}
		}
		return true;
	}
	return false;
}

void PowerupManager::manageLifetime(std::vector<std::shared_ptr<Powerup>>& powerups)
{
	powerups.erase(std::remove_if(powerups.begin(), powerups.end(), [](std::shared_ptr<Powerup> powerup)
		{
			if (!powerup->alive()) {
				return true;
			}
			else
				return false;
		}), powerups.end());
}

void PowerupManager::updatePowerups(std::vector<std::shared_ptr<Powerup>>& powerups, SpaceshipPlayer* player)
{
	for (auto& powerup : powerups) {

		powerup->update(player);
	}
}

void PowerupManager::renderPowerups(std::vector<std::shared_ptr<Powerup>>& powerups, sf::RenderTarget* target)
{
	for (auto& powerup : powerups) {

		powerup->render(target);
	}
}