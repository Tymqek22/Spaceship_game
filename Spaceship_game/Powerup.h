#pragma once

#include <SFML/Graphics.hpp>

#include "SpaceshipPlayer.h"

class Powerup
{
protected:
	sf::RectangleShape m_powerup;
	SpaceshipPlayer* m_hostSpaceship;
	bool m_activated;
	bool m_alive;
	sf::Clock m_timer;

public:
	Powerup() : m_hostSpaceship{nullptr}, m_activated{ false }, m_alive{ true } {}

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::FloatRect getAreaToCheck() const;

	bool collision(const sf::FloatRect& object);
	bool hasGone();
	bool alive();

	virtual void activate() = 0;

	void update(SpaceshipPlayer* spaceship);
	void render(sf::RenderTarget* target);
};

