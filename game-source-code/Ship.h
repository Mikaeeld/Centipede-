#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class Ship : public GameEntity
{
public:
	Ship();

	~Ship() {}

	constexpr static const float MAX_X = 240.0f - 4.0f; // 256 - 8
	constexpr static const float MAX_Y = 248.0f - 4.0f;
	constexpr static const float MIN_X = 3.0f;
	constexpr static const float MIN_Y = 200.0f + 4.0f;

	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	enum class Condition{
		Alive,
		Dying
	};

	void inputMove(Direction direction, sf::Time time);
	void tick(const sf::Time &time);
	void handleCollision(entityType type, sf::FloatRect collisionRect);
	void fire();
	void explode();
	void normal();

	entityType getType();

private:
	void handleInput(sf::Time time);
	void checkBounds();
	Direction direction_;
	float reload_;
	Condition condition_;
};