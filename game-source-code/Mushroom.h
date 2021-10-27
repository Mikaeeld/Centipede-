#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include "ResourcePath.h"
#include "Random.h"

using Texture_ptr = shared_ptr<sf::Texture>;

/**
 * @brief Mushroom class
 * 
 * Mushrooms are static objects that other entities can collide with
 * They take 4 shots from the player ot destroy
 * 
 */
class Mushroom : public GameEntity
{
public:
    /**
     * @brief Construct a new Mushroom object
     * 
     */
    Mushroom();

    /**
     * re-implemented functions
     */
    bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);
    entityType getType();
    void tick(const sf::Time &time);

private:
    float life_;
    bool shot_;
    float spiderTime_ = 0.8f;
};