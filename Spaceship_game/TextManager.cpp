#include "TextManager.h"

#include <sstream>
#include <iomanip>

TextManager::TextManager() {}

TextManager::~TextManager()
{
	for (auto& message : m_messagesMap) {

		delete message.second;
	}
}

void TextManager::addMessage(const MessageType& type, const std::string& message, const sf::Vector2f& position, 
	unsigned int size, const sf::Color& color)
{
	auto foundMessage = m_messagesMap.find(type);

	if (foundMessage == m_messagesMap.end()) {

		TextMessage* newMessage = new TextMessage(message, position, size, type, color);
		m_messagesMap.insert(std::pair<MessageType, TextMessage*>(newMessage->getType(), newMessage));
	}
}

void TextManager::manageLifetime(bool shipPowerupActive)
{
	if (shipPowerupActive) {

		this->addMessage(MessageType::powerupTimer, "", sf::Vector2f(10.f, 40.f), 50, sf::Color::White);
	}
	else {
		auto messageFound = m_messagesMap.find(MessageType::powerupTimer);

		if (messageFound != m_messagesMap.end()) {

			delete messageFound->second;
			m_messagesMap.erase(messageFound->first);
		}
	}
}

void TextManager::clear()
{
	for (auto& message : m_messagesMap) {

		delete message.second;
	}

	m_messagesMap.clear();
}

void TextManager::startGame()
{
	TextMessage* score = new TextMessage("Score: 0", sf::Vector2f(10.f, 10.f), 30, MessageType::score);

	m_messagesMap.insert(std::pair<MessageType, TextMessage*>(score->getType(), score));
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
	for (auto& message : m_messagesMap) {

		switch (message.first) {

		case MessageType::score:
			message.second->update<int>("Score", score);
			break;
		case MessageType::powerupTimer:
			message.second->update<float>(this->getPowerupType(powerup), time);
			break;
		}
	}
}

void TextManager::renderAll(sf::RenderTarget* target)
{
	for (auto& message : m_messagesMap) {

		message.second->render(target);
	}
}