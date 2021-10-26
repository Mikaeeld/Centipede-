#include "Explosion.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

Explosion::Explosion()
{
    this->dynamic_ = true;
    Texture_ptr normal(new sf::Texture());
    Texture_ptr break1(new sf::Texture());
    Texture_ptr break2(new sf::Texture());
    Texture_ptr break3(new sf::Texture());

    const string base = resourcePath() + "Sprites/DDT/";

    if (!normal->loadFromFile(base + "Explosion1.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break1->loadFromFile(base + "Explosion2.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break2->loadFromFile(base + "Explosion3.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break3->loadFromFile(base + "Explosion4.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    this->setPeriod(1.5);

    this->addKeyFrame(KeyFrame(0.0, normal));
    this->addKeyFrame(KeyFrame(10.0, break1));
    this->addKeyFrame(KeyFrame(20.0, break2));
    this->addKeyFrame(KeyFrame(30.0, break3));
    this->addKeyFrame(KeyFrame(20.0, break2));
    this->addKeyFrame(KeyFrame(40.0, break3));
    this->addKeyFrame(KeyFrame(50.0, break2));
    this->addKeyFrame(KeyFrame(60.0, break3));
    this->addKeyFrame(KeyFrame(70.0, break2));
    this->addKeyFrame(KeyFrame(80.0, break3));
    this->addKeyFrame(KeyFrame(90.0, break1));
    this->addKeyFrame(KeyFrame(100.0, normal));
    this->setAnimateMode(AnimateMode::once);
}

void Explosion::tick(const sf::Time &time)
{
    (void)time;
    if (animateDone())
    {
        this->toDelete_ = true;
    }
}

bool Explosion::handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other)
{
    (void)other;
    (void)collisionRect;
    switch (type)
    {
    default:
    {
        return false;
        break;
    }
    }
}

GameEntity::entityType Explosion::getType()
{
    return GameEntity::entityType::Explosion;
}