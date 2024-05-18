#include "TextMessage.h"
#include <sstream>
#include <iomanip>

TextMessage::TextMessage(const std::string& content, const sf::Vector2f& position, const MessageType& type, bool alive)
	: m_content{ content }, m_position{ position }, m_messageType{ type }, m_alive{ alive }
{
	m_font.loadFromFile("Font/Retro_Gaming.ttf");
	m_message.setFont(m_font);
	m_message.setString(content);
	m_message.setPosition(m_position);
	m_message.setFillColor(sf::Color::White);
}

MessageType TextMessage::getType() const
{
	return m_messageType;
}

bool TextMessage::isAlive() const
{
	return m_alive;
}

void TextMessage::activate()
{
	m_alive = true;
}

void TextMessage::deactivate()
{
	m_alive = false;
}

void TextMessage::render(sf::RenderTarget* target)
{
	target->draw(m_message);
}