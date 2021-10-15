#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class Ship : public GameEntity
{
public:
	Ship();

	~Ship() {}

	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};
	void inputMove(Direction direction, sf::Time time);
	void tick(sf::Time time);

private:
	void handleInput(sf::Time time);
};