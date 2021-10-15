#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class Mushroom : public GameEntity
{
public:
    Mushroom();
    ~Mushroom() {}

    entityType getType();
};