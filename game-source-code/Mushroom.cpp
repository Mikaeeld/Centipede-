#include "Mushroom.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

Mushroom::Mushroom()
{
    Texture_ptr normal(new sf::Texture());
    Texture_ptr break1(new sf::Texture());
    Texture_ptr break2(new sf::Texture());
    Texture_ptr break3(new sf::Texture());

    this->originAtCenter_ = false;
    this->dynamic_ = false;

    const string base = resourcePath() + "Sprites/Mushroom/";

    if (!normal->loadFromFile(base + "Mushroom1.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break1->loadFromFile(base + "Mushroom2.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break2->loadFromFile(base + "Mushroom3.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break3->loadFromFile(base + "Mushroom4.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    this->setPeriod(3.0);

    this->addKeyFrame(KeyFrame(0.0, normal));
    this->addKeyFrame(KeyFrame(25.0, break1));
    this->addKeyFrame(KeyFrame(50.0, break2));
    this->addKeyFrame(KeyFrame(75.0, break3));
    this->setAnimateMode(AnimateMode::pause);
    life_ = 0;
}

bool Mushroom::handleCollision(entityType type, sf::FloatRect collisionRect)
{
    (void)collisionRect;
    switch (type)
    {
    case entityType::Bullet:
    {
        if (!shot_)
        {
            shot_ = true;
            this->life_ += 25.0;
            if (life_ >= 100.f)
            {
                this->toDelete_ = true;
                life_ = 76.f;
            }
            this->setAnimateStart(life_);
            this->setAnimateMode(AnimateMode::pause);
        }
        break;
    }
    case entityType::Explosion:
    case entityType::DDT:
    {
        this->toDelete_ = true;
        break;
    }
    default:
    {
        return false;
        break;
    }
    }

    return true;
}

GameEntity::entityType Mushroom::getType()
{
    return GameEntity::entityType::Mushroom;
}