#pragma once

#include "game/game.hpp"
#include "view/menu/menu.hpp"

class MenuState : public GameState {
public:
	MenuState(const sf::Font& font, const sf::Vector2u dimensions);
	~MenuState() = default;

	auto tick(float dt, sf::RenderWindow& window) -> bool final;

private:
	Pong::Menu m_menu;
};
