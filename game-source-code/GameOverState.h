#pragma once
#include "State.h"
#include "ResourcePath.h"
#include "SFML/Graphics.hpp"

/**
 * @brief This state is present when the game has completed
 *
 * The player can press enter to restart the game, or escape to quit.
 *
 */
class GameOverState : public State
{
public:
	/**
	 * @brief Construct a new Game Over State object
	 *
	 * @param windowSize  A vector containing the window size
	 */
	GameOverState(const sf::Vector2f &windowSize);

	// Re-implemented functions
	const vector<Drawable_ptr> getDrawable();
	void handleInput();

private:
	shared_ptr<sf::Sprite> gameOver_;
	shared_ptr<sf::Texture> gameOverImage_;
};