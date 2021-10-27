#pragma once
#include "State.h"
#include "ResourcePath.h"
#include "SFML/Graphics.hpp"

class GameOverState : public State
{
public:
	GameOverState(const sf::Vector2f &windowSize);

	const vector<Drawable_ptr> getDrawable();

	void handleInput();

private:
	shared_ptr<sf::Sprite> gameOver_;
	shared_ptr<sf::Texture> gameOverImage_;
};