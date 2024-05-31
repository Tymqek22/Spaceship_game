#pragma once

#include <SFML/Graphics.hpp>

#include "Asteroid.h"

class Bullet
{
private:
	bool m_alive;

	sf::RectangleShape m_bullet;
	sf::Vector2f m_startPosition;

public:
	Bullet(const sf::Vector2f& startPos);
	~Bullet();

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	bool getAliveStatus() const;

	void hit();

	bool wallCollision();
	bool objectCollision(const sf::FloatRect& area);
	void update();
	void enemyUpdate();
	void render(sf::RenderTarget* target);
};
