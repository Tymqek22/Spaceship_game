#include "AsteroidManager.h"

void AsteroidManager::manageLifetime(std::vector<Asteroid*>& asteroids)
{
	for (int i = 0; i < asteroids.size(); i++) {

		if (!asteroids[i]->getAliveStatus()) {

			delete asteroids[i];
			asteroids.erase(asteroids.begin() + i);
		}
	}
}

void AsteroidManager::manageAsteroids(std::vector<Asteroid*>& asteroids, SpaceshipPlayer& player)
{

	for (auto& asteroid : asteroids) {

		if (asteroid->asteroidCollision(player.getAreaToCheck()) && !player.hasAShield()) {
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