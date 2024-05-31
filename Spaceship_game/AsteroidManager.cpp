#include "AsteroidManager.h"
#include <algorithm>

void AsteroidManager::manageLifetime(std::vector<Asteroid*>& asteroids)
{
	asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid* asteroid)
		{
			if (!asteroid->getAliveStatus()) {
				delete asteroid;
				return true;
			}
			else
				return false;
		}), asteroids.end());
}

void AsteroidManager::manageAsteroids(std::vector<Asteroid*>& asteroids, SpaceshipPlayer& player)
{
	for (auto& asteroid : asteroids) {

		if (asteroid->objectCollision(player.getAreaToCheck()) && !player.hasAShield()) {
			player.hit();
			asteroid->hit();
		}
		else {
			asteroid->update();
		}
	}
}

void AsteroidManager::renderAsteroids(std::vector<Asteroid*>& asteroids, sf::RenderTarget* target)
{
	for (auto& asteroid : asteroids) {

		asteroid->render(target);
	}
}