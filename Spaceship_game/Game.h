#pragma once

#include <SFML/Graphics.hpp>

#include "SpaceshipPlayer.h"
#include "SpaceshipEnemy.h"
#include "Asteroid.h"
#include "TextManager.h"
#include "Powerup.h"
#include "HealthBar.h"

//TODO: komunikaty game over, info o powerupie, press start

class Game
{
private:
	sf::RenderWindow* m_window;
	sf::Event m_ev;
	TextManager m_text;
	sf::Clock m_powerupTimer;
	float m_asteroidBooster;

	SpaceshipPlayer m_ship;
	SpaceshipEnemy m_enemy;
	std::vector<Asteroid*> m_asteroids;
	std::vector<Powerup*> m_powerups;

	void createAsteroids();

public:
	Game();
	~Game();

	bool isRunning() const;

	void pollEvents();
	void managePowerups();

	void update();
	void render();
	void bossFightUpdate();
	void normalLevelUpdate();
	void normalLevelRender();
	void bossFightRender();
};

