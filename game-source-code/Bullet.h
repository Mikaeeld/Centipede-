#pragma once
#include "GameEntity.h"
#include "SFML/Graphics.hpp"
#include "Ship.h"

using Texture_ptr = shared_ptr<sf::Texture>;

/**
 * @brief Bullet GameEntity
 *
 * Bullets are fired from the Ship and could potentially collide with enemies.
 * Also known as 'Lasers'
 */
class Bullet : public GameEntity
{
public:
	/**
	 * @brief Construct a new Bullet object
	 *
	 */
	Bullet();

	void tick(const sf::Time &time);

	/**
	 * @brief Stores the minimum Y position of the bullet
	 *
	 */
	constexpr static const float MIN_Y = -7.0f;

	/**
	 * @brief Stores the Velocity in pixels/second at which the bullet travels
	 *
	 */
	static const sf::Vector2f VELOCITY;

	bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);
	entityType getType();

private:
};