#pragma once

#include "game/game.hpp"
#include "view/menu/menu.hpp"

class MenuState : public GameState {
public:
	/**
	 * @brief Inherited from GameState.
	 */
	MenuState(const sf::Font& font, const sf::Vector2u dimensions);

	/**
	 * @brief Inherited from GameState.
	 */
	~MenuState() = default;

	/**
	 * @brief Inherited from GameState.
	 */
	auto tick(float dt, sf::RenderWindow& window) -> bool final;

private:
	Pong::Menu m_menu;
};
