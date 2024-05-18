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

	
	void update(int score, float time);
	void renderAll(sf::RenderTarget* target);
};