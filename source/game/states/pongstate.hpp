#pragma once

#include "game/game.hpp"
#include "view/ball/ball.hpp"
#include "view/player/player.hpp"
#include "view/text/text.hpp"

#include <SFML/Audio.hpp>

#include <iostream>

class PongState : public GameState {
public:
	/**
	 * @brief Inherited from GameState.
	 */
	PongState(sf::Font& font, const sf::Vector2u& dimensions);

	/**
	 * @brief Inherited from GameState.
	 */
	~PongState() = default;

	/**
	 * @brief Inherited from GameState.
	 */
	auto tick(const double& dt, sf::RenderWindow& window) -> bool final;

private:
	auto init_game(const sf::Vector2u& dimensions) -> void;
	auto init_sounds() -> void;

	auto end_game() -> void;

	auto handle_scores_ball_reset(int& player_score, Pong::Text& score_label,
								  Ball& ball, unsigned int& rounds,
								  const sf::Vector2f& window_size) -> void;

	auto check_collision(sf::RectangleShape& one, sf::RectangleShape& two)
		-> bool;

	Player m_player_one;
	Player m_player_two;

	int m_p1_score;
	int m_p2_score;

	unsigned int m_rounds{1};

	Pong::Text m_p1_score_label;
	Pong::Text m_p2_score_label;

	Pong::Text m_game_over_label;
	Pong::Text m_winner_label;

	Ball m_ball;

	// Load a sound buffer
	// Create a sound object and set its buffer
	sf::SoundBuffer collision_sound_buffer;
	sf::Sound collision_sound;

	sf::SoundBuffer oob_sound_buffer;
	sf::Sound oob_sound;

	sf::SoundBuffer end_sound_buffer;
	sf::Sound end_sound;
};
