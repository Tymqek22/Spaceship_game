#pragma once

#include "Bullet.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

class Spaceship
{
protected:
	float SHIP_SPEED = 8.f;

	sf::Texture m_texture;
	sf::Sprite m_entity;
	std::vector<Bullet> m_bulletsShot;
	sf::Clock m_clock;

public:
	Spaceship() = default;
	virtual ~Spaceship() = default;
	
	sf::Vector2f getWeaponPosition() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::FloatRect getAreaToCheck() const;

	virtual void shoot() = 0;
	virtual void hit() = 0;
	virtual bool hasAShield() = 0;

	virtual void updateShip() = 0;
	void renderShip(sf::RenderTarget* target);
	void renderBullets(sf::RenderTarget* target);

};