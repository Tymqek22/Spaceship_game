#pragma once

#include "SpaceshipPlayer.h"
#include "TextMessage.h"

#include <SFML/Graphics.hpp>


class TextManager
{
private:
	std::vector<TextMessage*> m_messages;

public:
	TextManager();
	~TextManager();

	void manageLifetime(bool shipPowerupActive);
	std::string getPowerupType(const PowerupType& powerup);
	
	void update(int score, float time, const PowerupType& powerup);
	void renderAll(sf::RenderTarget* target);
};