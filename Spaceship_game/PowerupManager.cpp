#include "PowerupManager.h"
#include "PowerupReloadTime.h"
#include "PowerupShield.h"
#include "PowerupMultishoot.h"
#include <random>

bool PowerupManager::createPowerup(float time, std::vector<Powerup*>& powerups)
{
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<int> powerupChoosing{ 1,3 };

	if (time >= 10.f) {

		int randomPowerup = powerupChoosing(mt);

		switch (randomPowerup) {
		case 1: {
			Powerup* powerup = new PowerupReloadTime();
			powerups.push_back(powerup);
			break;
		}
		case 2: {
			Powerup* powerup = new PowerupShield();
			powerups.push_back(powerup);
			break;
		}
		case 3: {
			Powerup* powerup = new PowerupMultishoot();
			powerups.push_back(powerup);
			break;
		}
		}
		return true;
	}
	return false;
}

void PowerupManager::manageLifetime(std::vector<Powerup*>& powerups)
{
	for (int i = 0; i < powerups.size(); i++) {

		if (!powerups[i]->alive()) {

			delete powerups[i];
			powerups.erase(powerups.begin() + i);
		}
	}
}

void PowerupManager::updatePowerups(std::vector<Powerup*>& powerups, SpaceshipPlayer* player)
{
	for (auto& powerup : powerups) {

		powerup->update(player);
	}
}

void PowerupManager::renderPowerups(std::vector<Powerup*>& powerups, sf::RenderTarget* target)
{
	for (auto& powerup : powerups) {

		powerup->render(target);
	}
}