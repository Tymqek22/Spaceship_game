#pragma once

#include <memory>

#include "Asteroid.h"
#include "SpaceshipPlayer.h"

class AsteroidManager
{
public:
	AsteroidManager() = default;

	void manageLifetime(std::vector<std::shared_ptr<Asteroid>>& asteroids);
	void manageAsteroids(std::vector<std::shared_ptr<Asteroid>>& asteroids, SpaceshipPlayer& player);
	void renderAsteroids(std::vector<std::shared_ptr<Asteroid>>& asteroids, sf::RenderTarget* target);

};

