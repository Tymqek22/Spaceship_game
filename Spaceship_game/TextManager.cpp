#include "TextManager.h"

#include <sstream>
#include <iomanip>

TextManager::TextManager()
{
	TextMessage* score = new TextMessage("Score: 0", sf::Vector2f(10.f, 10.f), MessageType::score, true);
	TextMessage* powerupInfo = new TextMessage(" ", sf::Vector2f(10.f, 40.f), MessageType::powerupTimer, false);

	m_messages.push_back(score);
	m_messages.push_back(powerupInfo);
}

TextManager::~TextManager()
{
	for (auto& message : m_messages) {

		delete message;
	}
}

void TextManager::manageLifetime(bool shipPowerupActive)
{
	if (shipPowerupActive) {

		m_messages[1]->activate();
	}
	else {

		m_messages[1]->deactivate();
	}
}

std::string TextManager::getPowerupType(const PowerupType& powerup)
{
	std::string powerupName;

	switch (powerup) {

	case PowerupType::reloadTime: 
		powerupName = "Quick shoot";
		break;
	case PowerupType::shield:
		powerupName = "Shield";
		break;
	case PowerupType::multishoot:
		powerupName = "Multishoot";
		break;
	}

	return powerupName;
}

void TextManager::update(int score, float time, const PowerupType& powerup)
{
	for (auto& message : m_messages) {

		if (message->isAlive()) {

			switch (message->getType()) {

			case MessageType::score:
				message->update<int>("Score", score);
				break;
			case MessageType::powerupTimer:
				message->update<float>(this->getPowerupType(powerup), time);
				break;
			}
		}
	}
}

void TextManager::renderAll(sf::RenderTarget* target)
{
	for (auto& message : m_messages) {

		if (message->isAlive()) {

			message->render(target);
		}
		
	}
}