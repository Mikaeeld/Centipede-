#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class Mushroom : public GameEntity
{
public:
    Mushroom();
    ~Mushroom() {}

    bool handleCollision(entityType type, sf::FloatRect collisionRect);
    entityType getType();
    void tick(const sf::Time &time)
    {
        (void)time;
        shot_ = false;
    }

private:
    float life_;
    bool shot_;
};