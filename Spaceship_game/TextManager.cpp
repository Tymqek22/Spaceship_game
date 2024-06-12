#include "TextManager.h"

#include <sstream>
#include <iomanip>


void TextManager::addMessage(const MessageType& type, const std::string& message, const sf::Vector2f& position, 
	unsigned int size, const sf::Color& color)
{
	auto foundMessageType = m_messagesMap.find(type);

	if (foundMessageType == m_messagesMap.end()) {

		std::shared_ptr<TextMessage> newMessage = std::make_shared<TextMessage>(message, position, size, type, color);
		m_messagesMap.insert(std::pair<MessageType, std::shared_ptr<TextMessage>>(newMessage->getType(), newMessage));
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

			m_messagesMap.erase(messageFound->first);
		}
	}
}

void TextManager::clear()
{
	m_messagesMap.clear();
}

void TextManager::startGame()
{
	std::shared_ptr<TextMessage> score = std::make_shared<TextMessage>("Score: 0", sf::Vector2f(10.f, 10.f), 30, MessageType::score);

	m_messagesMap.insert(std::pair<MessageType, std::shared_ptr<TextMessage>>(score->getType(), score));
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