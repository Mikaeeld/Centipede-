#include "DDT.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

DDT::DDT()
{
    Texture_ptr normal(new sf::Texture());

    const string base = resourcePath() + "Sprites/DDT/";

    if (!normal->loadFromFile(base + "DDT.png"))
        throw std::runtime_error("Cannot Load Ship Image");
    this->addKeyFrame(KeyFrame(0.0, normal));
    this->setAnimateMode(AnimateMode::pause);
}

void DDT::handleCollision(entityType type, sf::FloatRect collisionRect)
{
    switch (type)
    {
    case entityType::Bullet:
    {
        {
            createQueue_.push(pair<GameEntity::entityType, sf::Vector2f>{GameEntity::entityType::Explosion, sf::Vector2f{getPosition().x, getPosition().y}});
            this->toDelete_ = true;
        }
    }
    default:
    {
    }
    }
}

GameEntity::entityType DDT::getType()
{
    return GameEntity::entityType::DDT;
}