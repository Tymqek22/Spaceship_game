#include "TextMessage.h"
#include <sstream>
#include <iomanip>


TextMessage::TextMessage(const std::string& content, const sf::Vector2f& position, unsigned int size, const MessageType& type,
	const sf::Color& color)
	: m_content{ content }, m_position{ position }, m_size{ size }, m_messageType{ type }, m_scale{ 1.f }
{
	m_font.loadFromFile("Font/Retro_Gaming.ttf");
	m_message.setFont(m_font);
	m_message.setString(content);
	m_message.setPosition(m_position);
	m_message.setCharacterSize(m_size);
	m_message.setFillColor(color);
}

MessageType TextMessage::getType() const
{
	return m_messageType;
}

void TextMessage::render(sf::RenderTarget* target)
{
	target->draw(m_message);
}