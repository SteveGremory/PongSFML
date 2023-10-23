#pragma once

#include "game/game.hpp"
#include "view/ball/ball.hpp"
#include "view/player/player.hpp"
#include "view/text/text.hpp"

#include <iostream>

class PongState : public GameState {
public:
	PongState(sf::Font& font);
	~PongState() = default;

	auto tick(float dt, sf::RenderWindow& window) -> bool final;

	auto check_collision(sf::RectangleShape& one, sf::RectangleShape& two)
		-> bool;

private:
	Player m_player_one;
	Player m_player_two;

	size_t m_p1_score;
	size_t m_p2_score;

	Pong::Text m_p1_score_label;
	Pong::Text m_p2_score_label;

	Ball m_ball;
};
