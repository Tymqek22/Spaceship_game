#pragma once

#include "Bullet.h"
#include "HealthBar.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Spaceship
{
protected:
	float m_healthPoints;
	sf::Texture m_texture;
	sf::Sprite m_entity;
	HealthBar m_healthBar;
	std::vector<Bullet> m_bulletsShot;
	sf::Clock m_clock;

public:
	Spaceship() = default;
	virtual ~Spaceship() = default;
	
	sf::Vector2f getCenterPosition() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::FloatRect getAreaToCheck() const;
	float getHealth() const;

	virtual void shoot() = 0;
	virtual void hit() = 0;
	virtual bool hasAShield() = 0;

	virtual void updateShip() = 0;
	void renderShip(sf::RenderTarget* target, bool withHealthBar);
	void renderBullets(sf::RenderTarget* target);

};