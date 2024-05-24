#pragma once
#include <SFML/Graphics.hpp>

constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 800;

const sf::Vector2f BULLET_SIZE = { 10.0f, 10.0f };
const sf::Vector2f HPBASEBAR_SIZE = { 80.0f, 8.0f };
const sf::Vector2f HPDYNAMICBAR_SIZE = { 78.0f, 6.0f };
const sf::Vector2f POWERUP_SIZE = { 20.0f, 20.0f };

constexpr float PLAYER_SPEED = 8.0f;
constexpr float ENEMY_SPEED = 2.0f;
constexpr float BULLET_SPEED = 12.0f;
constexpr float POWERUP_SPEED = 5.0f;

constexpr float PLAYER_HEALTH = 50;
constexpr float ENEMY_HEALTH = 50;

constexpr float ASTEROID_BOOSTER = 0.1f;

constexpr float PLAYERSHOOTING_COOLDOWN = 0.5f;
constexpr float ENEMYSHOOTING_COOLDOWN = 1.0f;
constexpr float POWERUP_COOLDOWN = 4.0f;
constexpr float POWERUP_TIMER = 15.0f;