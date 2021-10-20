#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class DDT : public GameEntity
{
public:
    DDT();
    ~DDT() {}

    bool handleCollision(entityType type, sf::FloatRect collisionRect);
    entityType getType();
};