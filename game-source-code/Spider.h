#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include "Random.h"

using Texture_ptr = shared_ptr<sf::Texture>;

/**
 * @brief Spider class
 * 
 * Moves randomly within the bottom 3rd of the screen
 * Ocassionally eats mushrooms
 * 
 */
class Spider : public GameEntity
{
public:
    /**
     * @brief Construct a new Spider object
     * 
     */
    Spider();

    //Spider movement bounds
    constexpr static const float MAX_X = 240.0f - 8.0f; // 256 - 8
    constexpr static const float MAX_Y = 248.0f - 4.0f;
    constexpr static const float MIN_X = 8.0f;
    constexpr static const float MIN_Y = 160.0f + 4.0f;
    /**
     * @brief Possible directions for movement
     * 
     */
    enum class Direction
    {
        Left,
        Right,
        Up,
        Down,
        None
    };

    //Reimplemented functions
    void tick(const sf::Time &time);
    bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);
    entityType getType();

private:
    void checkBounds();
    void randomizeDirection(const sf::Time &time);
    void tickMove(const sf::Time &time);
    float randomizeTime_ = 3.0f;
    Direction xDirection_ = Direction::None;
    Direction yDirection_ = Direction::None;
};