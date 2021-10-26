#include "Spider.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

Spider::Spider()
{
    this->dynamic_ = true;
    Texture_ptr normal(new sf::Texture());
    Texture_ptr break1(new sf::Texture());
    Texture_ptr break2(new sf::Texture());
    Texture_ptr break3(new sf::Texture());

    const string base = resourcePath() + "Sprites/Spider/";

    if (!normal->loadFromFile(base + "Spider1.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break1->loadFromFile(base + "Spider2.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break2->loadFromFile(base + "Spider3.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    if (!break3->loadFromFile(base + "Spider4.png"))
        throw std::runtime_error("Cannot Load Ship Image");

    this->setPeriod(0.5);

    this->addKeyFrame(KeyFrame(0.0, normal));
    this->addKeyFrame(KeyFrame(25.0, break1));
    this->addKeyFrame(KeyFrame(50.0, break2));
    this->addKeyFrame(KeyFrame(75.0, break3));
    this->setAnimateMode(AnimateMode::loop);
    xDirection_ = Spider::Direction::Right;
    yDirection_ = Spider::Direction::Down;
}

void Spider::tick(const sf::Time &time)
{
    randomizeDirection(time);
    checkBounds();
    tickMove(time);
}

void Spider::randomizeDirection(const sf::Time &time)
{
    randomizeTime_ -= time.asSeconds();

    if (randomizeTime_ < 0)
    {
        randomizeTime_ = 1.5f;
        // 50% chance to change x direction
        if (true)
        {
            if (randomBool())
            {
                xDirection_ = Spider::Direction::Left;
            }
            else
            {
                xDirection_ = Spider::Direction::Right;
            }
        }
        // ditto for y
        if (true)
        {
            if (randomBool(0.3f))
            {
                yDirection_ = Spider::Direction::Up;
            }
            else
            {
                yDirection_ = Spider::Direction::Down;
            }
        }
        // 30% chance for stopping movement in x or y;
        if (randomBool(0.3f))
        {
            if (yDirection_ != Spider::Direction::None)
            {
                xDirection_ = Spider::Direction::None;
            }
        }
        if (randomBool(0.3f))
        {
            if (xDirection_ != Spider::Direction::None)
            {
                yDirection_ = Spider::Direction::None;
            }
        }
    }
}

void Spider::tickMove(const sf::Time &time)
{
    auto distance = 25.f * time.asSeconds();
    switch (this->xDirection_)
    {
    case Spider::Direction::Left:
    {
        this->move(-distance, 0.f);
        break;
    }
    case Spider::Direction::Right:
    {
        this->move(distance, 0.f);
        break;
    }
    default:
    {
    }
    }

    switch (this->yDirection_)
    {

    case Spider::Direction::Up:
    {
        this->move(0.f, -distance);
        break;
    }
    case Spider::Direction::Down:
    {
        this->move(0.f, distance);
        break;
    }
    default:
    {
    }
    }
}

bool Spider::handleCollision(entityType type, sf::FloatRect collisionRect)
{
    (void)collisionRect;
    switch (type)
    {
    case entityType::Bullet:
    case entityType::Explosion:
    {
        this->toDelete_ = true;
        return true;
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

GameEntity::entityType Spider::getType()
{
    return GameEntity::entityType::Spider;
}

void Spider::checkBounds()
{
    auto current = this->getPosition();

    if (current.x > MAX_X)
    {
        this->xDirection_ = Spider::Direction::Left;
    }
    else if (current.x < MIN_X)
    {
        this->xDirection_ = Spider::Direction::Right;
    }
    if (current.y > MAX_Y)
    {
        this->yDirection_ = Spider::Direction::Up;
    }
    else if (current.y < MIN_Y)
    {
        this->yDirection_ = Spider::Direction::Down;
    }
}