#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

/**
 * @brief DDT Game Entity
 *
 * A DDT bomb is a package for an explosion. When it is shot by a bullet it will turn into an explosion
 * (or DDT cloud) which will then kill all enemies that it touches as well as mushrooms.
 *
 * To be spawned randomly
 */
class DDT : public GameEntity
{
public:
    /**
     * @brief Construct a new DDT object
     *
     */
    DDT();

    /**
     * Re-implemented to handle collisions with bullet
     */
    bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);

    /**
     * Re-implemented to return DDT type
     */
    entityType getType();
};