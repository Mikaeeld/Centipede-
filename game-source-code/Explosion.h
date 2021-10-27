#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

/**
 * @brief Explosion (DDT Cloud) Game Entity
 *
 * Spawned when a DDT bomb is shot this Explosion entity will kill all enemies that it touches, including mushrooms.
 *
 */
class Explosion : public GameEntity
{
public:
    /**
     * @brief Construct a new Explosion object
     *
     */
    Explosion();

    /**
     * Re-implemented functions
     * */
    void tick(const sf::Time &time);
    bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);
    entityType getType();
};