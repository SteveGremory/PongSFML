#pragma once

#include "game/game.hpp"
#include "view/player/player.hpp"
#include "view/text/text.hpp"

#include <iostream>

class PongState : public GameState {
public:
	PongState(sf::Font& font);
	~PongState() = default;

	auto tick(float dt, sf::RenderWindow& window) -> bool final;

private:
	Player m_player_one;
	Player m_player_two;

	size_t p1_score;
	size_t p2_score;

	Pong::Text p1_score_label;
	Pong::Text p2_score_label;
};
