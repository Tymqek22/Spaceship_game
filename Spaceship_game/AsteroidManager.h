#pragma once

#include "Asteroid.h"
#include "SpaceshipPlayer.h"

class AsteroidManager
{
public:
	AsteroidManager() = default;

	void manageLifetime(std::vector<Asteroid*>& asteroids);
	void manageAsteroids(std::vector<Asteroid*>& asteroids, SpaceshipPlayer& player);
	void renderAsteroids(std::vector<Asteroid*>& asteroids, sf::RenderTarget* target);

};

