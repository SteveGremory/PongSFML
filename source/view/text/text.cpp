#include "text.hpp"

namespace Pong {

Text::Text(const std::string_view initial_text, const sf::Font& font,
		   unsigned int font_size)
	: m_text(font, initial_text.data(), font_size), m_position({0, 0}) {

	this->m_text.setFillColor(sf::Color::White);
	this->m_text.setStyle(sf::Text::Bold);

	this->center_text_anchor();
}

auto Text::center_text_anchor() -> void {
	this->m_text_rect = this->m_text.getLocalBounds();
	this->m_text.setOrigin(
		{this->m_text_rect.left + this->m_text_rect.width / 2.0f,
		 this->m_text_rect.top + this->m_text_rect.height / 2.0f});
}

auto Text::set_text(const std::string_view new_text) -> void {
	m_text.setString(new_text.data());
	this->center_text_anchor();
}

auto Text::set_position(const sf::Vector2f& position) -> void {
	m_text.setPosition(position);
}

auto Text::get_sfml_text() const -> sf::Text { return this->m_text; }

auto Text::get_position() const -> sf::Vector2f { return this->m_position; }

} // namespace Pong
