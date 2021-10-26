#include "DDT.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

DDT::DDT()
{
    Texture_ptr normal(new sf::Texture());
    dynamic_ = true;
    const string base = resourcePath() + "Sprites/DDT/";
    if (!normal->loadFromFile(base + "DDT.png"))
        throw std::runtime_error("Cannot Load Ship Image");
    this->addKeyFrame(KeyFrame(0.0, normal));
    this->setAnimateMode(AnimateMode::pause);
}

bool DDT::handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other)
{
    (void)other;
    (void)collisionRect;
    switch (type)
    {
    case entityType::Bullet:
    case entityType::Explosion:
    {
        {
            createQueue_.push(pair<GameEntity::entityType, sf::Vector2f>{GameEntity::entityType::Explosion, sf::Vector2f{getPosition().x, getPosition().y}});
            this->toDelete_ = true;

            return true;
            break;
        }
    }
    default:
    {
        return false;
        break;
    }
    }

    return true;
}

GameEntity::entityType DDT::getType()
{
    return GameEntity::entityType::DDT;
}