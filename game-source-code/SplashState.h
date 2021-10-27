#pragma once
#include "State.h"
#include "ResourcePath.h"
#include "SFML/Graphics.hpp"

class SplashState : public State
{
public:
	SplashState(const sf::Vector2f &windowSize);

	const vector<Drawable_ptr> getDrawable();
	void handleInput();

private:
	shared_ptr<sf::Sprite> splash_;
	shared_ptr<sf::Texture> splashImage_;
};