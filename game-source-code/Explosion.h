#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class Explosion : public GameEntity
{
public:
    Explosion();
    ~Explosion() {}

    void tick(const sf::Time &time);
    void handleCollision(entityType type, sf::FloatRect collisionRect);
    entityType getType();
};