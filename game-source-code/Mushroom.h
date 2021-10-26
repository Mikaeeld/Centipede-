#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include "ResourcePath.h"
#include "Random.h"

using Texture_ptr = shared_ptr<sf::Texture>;

class Mushroom : public GameEntity
{
public:
    Mushroom();
    ~Mushroom() {}

    bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);
    entityType getType();
    void tick(const sf::Time &time);

private:
    float life_;
    bool shot_;
    float spiderTime_ = 0.8f;
};