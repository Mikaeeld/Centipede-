#pragma once
#include "State.h"
#include "ResourcePath.h"
#include "SFML/Graphics.hpp"

/**
 * @brief This state presents a splash screen with the controls of the game
 *
 * The game begins when the enter key is pressed.
 * The game is exited when the escape key is pressed.
 */
class SplashState : public State
{
public:
	/**
	 * @brief Construct a new Splash State object
	 *
	 * @param windowSize  A vector containing the window size
	 */
	SplashState(const sf::Vector2f &windowSize);

	// Re-implemented functions
	const vector<Drawable_ptr> getDrawable();
	void handleInput();

private:
	shared_ptr<sf::Sprite> splash_;
	shared_ptr<sf::Texture> splashImage_;
};