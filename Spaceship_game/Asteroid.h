#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Asteroid
{
protected:
	float m_xDirection;
	float m_yDirection;

	float m_top;
	float m_bottom;
	float m_left;
	float m_right;

	bool m_alive;
	sf::Texture m_texture;
	sf::Sprite m_asteroid;

public:
	Asteroid(const sf::Texture& texture);
	~Asteroid();

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::FloatRect getAreaToCheck() const;
	float getTopBound() const;
	float getBottomBound() const;
	float getLeftBound() const;
	float getRightBound() const;
	bool getAliveStatus() const;

	void setBoost(float boost);
	void setDirection();
	void setPosition();
	void setBounds();
	void bounce();
	void hit();

	bool wallCollision();
	bool objectCollision(const sf::FloatRect& object);

	void update();
	void render(sf::RenderTarget* target);
};

