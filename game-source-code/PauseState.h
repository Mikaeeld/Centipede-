#pragma once
#include "State.h"
#include "ResourcePath.h"
#include "SFML/Graphics.hpp"

class PauseState : public State
{
public:
	PauseState(const sf::Vector2f &windowSize);

	const vector<Drawable_ptr> getDrawable();
	void update(const sf::Time &time);
	void handleInput();

private:
	shared_ptr<sf::Sprite> pause_;
	shared_ptr<sf::Texture> pauseImage_;
	float pauseDelay_;
};