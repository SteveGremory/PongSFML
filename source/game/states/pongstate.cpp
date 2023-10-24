#include "pongstate.hpp"

#include "utils/io.hpp"
#include "utils/physics.hpp"

constexpr auto PLAYER_SPEED = 1000.0f;
constexpr auto BALL_SPEED = 600.0f;
constexpr auto MAX_ROUNDS = 5;

constexpr auto SPRITE_HEIGHT = 120.0f;
constexpr auto SPRITE_WIDTH = 10.0f;

PongState::PongState(sf::Font& font, const sf::Vector2u& dimensions)
	// Init player characters
	: m_player_one({dimensions.x * 0.05f, dimensions.y * 0.5f}, dimensions.y,
				   {SPRITE_WIDTH, SPRITE_HEIGHT}),
	  m_player_two({dimensions.x * 0.95f, dimensions.y * 0.5f}, dimensions.y,
				   {SPRITE_WIDTH, SPRITE_HEIGHT}),

	  // Init player points
	  m_p1_score(0), m_p2_score(0),

	  // Init game labels
	  m_p1_score_label("0", font, Pong::FontSize::FONT_BIG),
	  m_p2_score_label("0", font, Pong::FontSize::FONT_BIG),
	  m_game_over_label("Game over!", font, Pong::FontSize::FONT_BIG),
	  m_winner_label("0", font, Pong::FontSize::FONT_MEDIUM),

	  // Init ball
	  m_ball({dimensions.x * 0.5f, dimensions.y * 0.5f}, {20, 20},
			 {BALL_SPEED, BALL_SPEED}),

	  // Init sounds
	  collision_sound(this->collision_sound_buffer),
	  oob_sound(this->oob_sound_buffer), end_sound(this->end_sound_buffer) {

	this->init_game(dimensions);
	this->init_sounds();
}

auto PongState::init_game(const sf::Vector2u& dimensions) -> void {
	// Set both the players' scores' positions.
	this->m_p1_score_label.set_position(
		{dimensions.x * 0.2f, dimensions.x * 0.1f});
	this->m_p2_score_label.set_position(
		{dimensions.x * 0.8f, dimensions.x * 0.1f});

	// Set the game over positions in advance.
	this->m_game_over_label.set_position(
		{dimensions.x * 0.5f, dimensions.y * 0.6f});
	this->m_winner_label.set_position(
		{dimensions.x * 0.5f, dimensions.y * 0.4f});
}

auto PongState::init_sounds() -> void {
	// Configure the sound
	utils::load_sound(this->collision_sound_buffer, "../assets/ball_smash.mp3");
	utils::load_sound(this->end_sound_buffer, "../assets/game_over.mp3");
	utils::load_sound(this->oob_sound_buffer, "../assets/out_of_bounds.mp3");

	this->collision_sound.setVolume(50.0f);
}

auto PongState::end_game() -> void {
	int pt_diff = std::abs(m_p1_score - m_p2_score);
	std::string winnerText;

	if (m_p1_score > m_p2_score) {
		winnerText = "P1 Wins by " + std::to_string(pt_diff) + " point(s)";
	} else {
		winnerText = "P2 Wins by " + std::to_string(pt_diff) + " point(s)";
	}

	m_winner_label.set_text(winnerText);

	this->m_p1_score_label.set_text(std::to_string(this->m_p1_score));
	this->m_p2_score_label.set_text(std::to_string(this->m_p2_score));

	// Internal state cleanup
	this->m_p1_score = 0;
	this->m_p2_score = 0;

	this->m_rounds = 1;

	this->end_sound.play();
}

auto PongState::handle_scores_ball_reset(int& player_score,
										 Pong::Text& score_label, Ball& ball,
										 unsigned int& rounds,
										 const sf::Vector2f& window_size)
	-> void {
	player_score++;
	rounds++;
	score_label.set_text(std::to_string(player_score));
	ball.reset({window_size.x * 0.5f, window_size.y * 0.5f},
			   {BALL_SPEED, BALL_SPEED});
}

auto PongState::tick(const double& dt, sf::RenderWindow& window) -> bool {

	if (this->m_rounds == MAX_ROUNDS + 1) {
		this->end_game();

		window.draw(this->m_game_over_label.get_sfml_text());
		window.draw(this->m_winner_label.get_sfml_text());

		window.display();

		// Wait for 5 seconds to display the main menu again
		sf::sleep(sf::seconds(5.0f));

		// Clear out any prev events in the buffer
		sf::Event event;
		while (window.pollEvent(event)) {
			continue;
		}
		return false;
	}

	sf::Event event;
	while (window.pollEvent(event)) {
		// If the close button was pressed
		// then close the window
		switch (event.type) {
		case sf::Event::Resized: {
			window.setSize({event.size.width, event.size.height});
			break;
		}

		case sf::Event::Closed:
			// Set should_exit to true so that
			// the state knows that we must close the window
			this->should_exit = true;
			return false;

			break;

		default:
			break;
		}
	}

	// Player movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->m_player_two.move(-PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->m_player_two.move(PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->m_player_one.move(-PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		this->m_player_one.move(PLAYER_SPEED * dt);
	}

	// Get SFML drawables all at once for later use.
	sf::RectangleShape& ball_drawable = m_ball.get_drawable();
	sf::RectangleShape& player_one_drawable = m_player_one.get_drawable();
	sf::RectangleShape& player_two_drawable = m_player_two.get_drawable();

	if (utils::check_collision(ball_drawable, player_one_drawable)) {

		// Left collision
		this->m_ball.reverse_velocity(player_one_drawable.getPosition());
		this->collision_sound.play();
	} else if (utils::check_collision(ball_drawable, player_two_drawable)) {

		// Right collision
		this->m_ball.reverse_velocity(player_two_drawable.getPosition());
		this->collision_sound.play();
	} else if (ball_drawable.getPosition().x <= 0.0f ||
			   ball_drawable.getPosition().x + ball_drawable.getSize().x >=
				   window.getView().getSize().x) {

		// Ball goes out of bounds
		int& player_score =
			(ball_drawable.getPosition().x <= 0.0f) ? m_p2_score : m_p1_score;
		// Who's score is to be incremented?
		Pong::Text& score_label = (ball_drawable.getPosition().x <= 0.0f)
									  ? m_p2_score_label
									  : m_p1_score_label;

		handle_scores_ball_reset(player_score, score_label, m_ball, m_rounds,
								 window.getView().getSize());

		// Play OOB sound effect
		this->oob_sound.play();
	} else {
		// only move the ball if required
		m_ball.move(dt, window.getView().getSize());
	}

	window.draw(ball_drawable);

	window.draw(player_one_drawable);
	window.draw(player_two_drawable);

	window.draw(this->m_p1_score_label.get_sfml_text());
	window.draw(this->m_p2_score_label.get_sfml_text());

	return true;
}
