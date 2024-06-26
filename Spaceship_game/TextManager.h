#pragma once

#include "SpaceshipPlayer.h"
#include "TextMessage.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>


class TextManager
{
private:
	std::map<MessageType, std::shared_ptr<TextMessage>> m_messagesMap;

public:
	TextManager() = default;
	~TextManager() = default;

	void addMessage(const MessageType& type, const std::string& message, const sf::Vector2f& position, unsigned int size,
		const sf::Color& color);
	void manageLifetime(bool shipPowerupActive);
	void clear();
	void startGame();
	std::string getPowerupType(const PowerupType& powerup);

	void update(int score, float time, const PowerupType& powerup);
	void renderAll(sf::RenderTarget* target);
};