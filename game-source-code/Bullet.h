#pragma once
#include "GameEntity.h"
#include "SFML/Graphics.hpp"
#include "Ship.h"

class Bullet : public GameEntity
{
public:
	Bullet();

	void tick(const sf::Time &time);
	constexpr static const float MIN_Y = -7.0f;

	static const sf::Vector2f VELOCITY;

private:
};