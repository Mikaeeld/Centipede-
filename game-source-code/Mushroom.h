#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

class Mushroom : public GameEntity
{
public:
    Mushroom();
    ~Mushroom() {}

    entityType getType();
};