#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "SpaceshipPlayer.h"
#include "SpaceshipEnemy.h"
#include "Asteroid.h"
#include "TextManager.h"
#include "Powerup.h"
#include "HealthBar.h"

class Game
{
private:
	sf::Texture m_texture;
	sf::Sprite m_background;
	sf::RenderWindow* m_window;
	sf::Event m_ev;
	TextManager m_text;
	sf::Clock m_powerupTimer;
	float m_asteroidBooster; 
	bool m_gameStarted;
	bool m_exit;

	SpaceshipPlayer m_ship;
	SpaceshipEnemy m_enemy;
	std::vector<std::shared_ptr<Asteroid>> m_asteroids;
	std::vector<std::shared_ptr<Powerup>> m_powerups;

	void createAsteroids();

public:
	Game();
	~Game();

	bool isRunning() const;
	bool gameStarted();
	bool exit();

	void pollEvents();
	void managePowerups();

	void startScreen();
	void endScreen();
	void update();
	void render();
	void bossFightUpdate();
	void normalLevelUpdate();
	void normalLevelRender();
	void bossFightRender();
};

