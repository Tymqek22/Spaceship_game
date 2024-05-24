#include <iostream>
#include <sstream>

#include "Game.h"
#include "AsteroidManager.h"
#include "PowerupManager.h"
#include "PowerupReloadTime.h"
#include "PowerupShield.h"
#include "PowerupMultishoot.h"
#include "Globals.h"

Game::Game() : m_asteroidBooster{ 0.f }, m_gameStarted{ false }, m_exit{ false }
{
	m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Spaceship Game", sf::Style::Default);
	m_window->setFramerateLimit(60);

	if (!m_texture.loadFromFile("Textures/Background.jpg")) {
		std::cerr << "Error with loading an image";
	}

	m_background.setTexture(m_texture);
	m_background.setPosition(0.f, 0.f);

	this->createAsteroids();
	m_enemy.setPlayerAsEnemy(&m_ship);
}

Game::~Game()
{
	for (auto& asteroid : m_asteroids) {
		delete asteroid;
	}

	for (auto& powerup : m_powerups) {
		delete powerup;
	}

	delete m_window;
}

void Game::createAsteroids()
{
	sf::Texture asteroidTexture;

	if (!asteroidTexture.loadFromFile("Textures/Asteroid.png")) {
		std::cerr << "Error opening a file.";
	}

	m_asteroids.reserve(5);
	for (int i = 0; i < 5; i++) {

		Asteroid* asteroid = new Asteroid(asteroidTexture);
		asteroid->setBoost(m_asteroidBooster);
		m_asteroids.push_back(asteroid);
	}
}

bool Game::isRunning() const
{
	return m_window->isOpen() && m_ship.isAlive();
}

bool Game::gameStarted()
{
	if (m_gameStarted) {
		m_powerupTimer.restart();
		return true;
	}
	
	return false;
}

bool Game::exit()
{
	return m_exit;
}

void Game::pollEvents()
{
	while (m_window->pollEvent(m_ev)) {

		switch (m_ev.type) {
		case sf::Event::Closed:
			m_exit = true;
			m_window->close();
			break;

		case sf::Event::KeyPressed: {
			if (m_ev.key.code == sf::Keyboard::Escape) {
				m_exit = true;
				m_window->close();
				break;
			}
			else if (m_ev.key.code == sf::Keyboard::Enter) {
				m_gameStarted = true;
				break;
			}
		}
		}
	}
}

void Game::managePowerups()
{
	sf::Time timer = m_powerupTimer.getElapsedTime();

	PowerupManager manager;
	if (manager.createPowerup(timer.asSeconds(), m_powerups)) {
		m_powerupTimer.restart();
	}

	manager.manageLifetime(m_powerups);
	manager.updatePowerups(m_powerups, &m_ship);
}

void Game::startScreen()
{
	sf::Font font;
	font.loadFromFile("Font/Retro_Gaming.ttf");
	sf::Text title("Space Shooting", font, 60);
	sf::Text text("Press [Enter] to start", font, 30);
	sf::Text userManual("Left - [Left arrow]\nRight - [Right arrow]\nShoot - [Space]\nExit - [Esc]", font, 17);
	sf::Text credits("Created by Tymoteusz Procner", font, 15);

	title.setPosition(220.f, 50.f);
	title.setFillColor(sf::Color::Yellow);
	text.setPosition(280.f, 200.f);
	text.setFillColor(sf::Color::White);
	userManual.setPosition(5.f, 680.f);
	userManual.setFillColor(sf::Color::White);
	credits.setPosition(660.f, 750.f);
	credits.setFillColor(sf::Color::White);
	this->pollEvents();

	m_window->clear();
	m_window->draw(m_background);
	m_window->draw(title);
	m_window->draw(text);
	m_window->draw(userManual);
	m_window->draw(credits);
	m_ship.renderShip(m_window, 0);

	m_window->display();
}

void Game::endScreen()
{
	sf::Font font;
	font.loadFromFile("Font/Retro_Gaming.ttf");

	sf::Text endingText("Game Over", font, 60);
	sf::Text userManual("Press [Esc] to exit", font, 20);
	sf::Text score("Your score: " + std::to_string(m_ship.getPoints()), font, 30);

	endingText.setPosition(300.f, 200.f);
	endingText.setFillColor(sf::Color::Yellow);
	score.setPosition(360.f, 300.f);
	score.setFillColor(sf::Color::White);
	userManual.setPosition(365.f, 370.f);
	userManual.setFillColor(sf::Color::White);
	

	this->pollEvents();

	m_window->clear();
	m_window->draw(m_background);
	m_ship.renderShip(m_window, 0);
	AsteroidManager manager;
	manager.renderAsteroids(m_asteroids, m_window);

	m_window->draw(endingText);
	m_window->draw(userManual);
	m_window->draw(score);

	m_window->display();
}

void Game::update()
{
	if (m_ship.getPoints() != 15) {

		this->normalLevelUpdate();
	}
	else {

		this->bossFightUpdate();
	}
}

void Game::render()
{
	if (m_ship.getPoints() != 15) {

		this->normalLevelRender();
	}
	else {

		this->bossFightRender();
	}
}

void Game::normalLevelUpdate()
{
	if (m_asteroids.size() == 0) {
		m_asteroidBooster += ASTEROID_BOOSTER;

		this->createAsteroids();
	}

	this->pollEvents();
	m_ship.updateShip();
	m_ship.updateBullets(m_asteroids);

	AsteroidManager manager;
	manager.manageLifetime(m_asteroids);
	manager.manageAsteroids(m_asteroids, m_ship);

	this->managePowerups();
	m_text.manageLifetime(m_ship.powerupActivated());
	m_text.update(m_ship.getPoints(), m_ship.getPowerupTimer(), m_ship.getPowerupType());
}

void Game::bossFightUpdate()
{
	this->pollEvents();
	m_ship.updateShip();
	m_ship.updateBulletsWithEnemy(&m_enemy);

	m_enemy.updateShip();
	m_enemy.updateBullets();

	m_text.manageLifetime(m_ship.powerupActivated());
	m_text.update(m_ship.getPoints(), m_ship.getPowerupTimer(), m_ship.getPowerupType());

	if (!m_enemy.isAlive()) {

		m_ship.setPoints(10);
	}
}

void Game::normalLevelRender()
{
	m_window->clear();
	m_window->draw(m_background);

	m_ship.renderShip(m_window, 1);
	m_ship.renderBullets(m_window);

	AsteroidManager manager;
	manager.renderAsteroids(m_asteroids, m_window);

	PowerupManager powerManager;
	powerManager.renderPowerups(m_powerups, m_window);

	m_text.renderAll(m_window);

	m_window->display();
}

void Game::bossFightRender()
{
	m_window->clear();
	m_window->draw(m_background);

	m_ship.renderShip(m_window, 1);
	m_ship.renderBullets(m_window);

	m_enemy.renderShip(m_window, 1);
	m_enemy.renderBullets(m_window);

	m_text.renderAll(m_window);

	m_window->display();
}