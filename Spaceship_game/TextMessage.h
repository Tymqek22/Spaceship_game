#pragma once
#include "Powerup.h"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <string>
#include <sstream>

enum class MessageType { score, powerupTimer };

class TextMessage
{
private:
	sf::Font m_font;
	sf::Text m_message;
	std::string m_content;
	sf::Vector2f m_position;
	unsigned int m_size;
	MessageType m_messageType;
	float m_scale;
	bool m_alive;
	

public:
	TextMessage(const std::string& content, const sf::Vector2f& position, unsigned int size, const MessageType& type, 
		bool alive);

	MessageType getType() const;
	bool isAlive() const;

	void activate();
	void deactivate();

	template <typename T>
	void update(const std::string& message, T number);
	void render(sf::RenderTarget* target);
};

template <typename T>
void TextMessage::update(const std::string& message, T number)
{
	switch (m_messageType) {

	case MessageType::score: {

		std::stringstream ss;
		ss << message << ": " << number;
		m_message.setString(ss.str());
		break;
	}
	case MessageType::powerupTimer: {

		m_scale -= 0.002f;
		std::stringstream ss;
		ss << message << ": " << std::fixed << std::setprecision(2) << number;
		if (message == "Quick shoot") {
			m_message.setFillColor(sf::Color::Red);
		}
		else if (message == "Shield") {
			m_message.setFillColor(sf::Color::Blue);
		}
		else if (message == "Multishoot") {
			m_message.setFillColor(sf::Color::White);
		}

		m_message.setString(ss.str());
		m_message.setScale(m_scale, m_scale);
		break;
	}
	}
}