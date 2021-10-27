#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

/**
 * @brief Ship Class
 * 
 * Ship (Player) entity
 * Moves on player input
 * Can fire bullets
 * Dies when hit by spider or centipede
 * 
 */
class Ship : public GameEntity
{
public:
	/**
	 * @brief Construct a new Ship object
	 * 
	 */
	Ship();

	//Ship movement bounds
	constexpr static const float MAX_X = 240.0f - 4.0f; // 256 - 8
	constexpr static const float MAX_Y = 248.0f - 4.0f;
	constexpr static const float MIN_X = 3.0f;
	constexpr static const float MIN_Y = 200.0f + 4.0f;

	/**
	 * @brief Possible ship movement directions
	 * 
	 */
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	/**
	 * @brief The state of the player
	 * 
	 */
	enum class Condition
	{
		Alive,
		Dying
	};

	/**
	 * @brief Moves the ship in the direction specified
	 * 
	 * @param direction Direction of movement
	 * @param time Tick time used to keep speed fixed
	 */
	void inputMove(Direction direction, sf::Time time);

	//Re-implemented funcitons
	void tick(const sf::Time &time);
	bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);
	entityType getType();
	
	/**
	 * @brief Fire a bullet from the ship and animate accordingly
	 * 
	 * Also ensures firing is rate limited
	 * 
	 */
	void fire();

	/**
	 * @brief Trigger the ship's explosion animation and enter the dying state
	 * 
	 */
	void explode();

	/**
	 * @brief Return the ship sprite to it's normal (non-firing) state
	 * 
	 */
	void normal();

	/**
	 * @brief Get the Condition of the ship
	 * 
	 * @return const Condition& 
	 */
	const Condition &getCondition()
	{
		return condition_;
	}


private:
	void handleInput(sf::Time time);
	void checkBounds();
	Direction direction_;
	float reload_;
	Condition condition_;
};