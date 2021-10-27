#pragma once
#include "State.h"
#include "ResourcePath.h"
#include "SFML/Graphics.hpp"

/**
 * @brief This sate pauses the game
 *
 * This state is mostly transparent the 'frozen' entities
 * from a Play state will be renderd underneath.
 */
class PauseState : public State
{
public:
	/**
	 * @brief Construct a new Pause State object
	 *
	 * @param windowSize A vector containing the window size
	 */
	PauseState(const sf::Vector2f &windowSize);

	// Re-implemented functions
	const vector<Drawable_ptr> getDrawable();
	void update(const sf::Time &time);
	void handleInput();

private:
	shared_ptr<sf::Sprite> pause_;
	shared_ptr<sf::Texture> pauseImage_;
	float pauseDelay_;
};