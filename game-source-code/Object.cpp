#include "Object.h"

Object::Object()
{
    shape_ = sf::CircleShape(100.0f);
    shape_.setFillColor(sf::Color::Blue);
    shape_.setOrigin(shape_.getRadius() / 2, shape_.getRadius() / 2);
    shape_.setPosition(sf::Vector2f{50, 250});
    offset_ = sf::Vector2f{50, -50};
}

Object::~Object()
{
}

void Object::tick(sf::Time time)
{
    auto elapsed = time.asSeconds();
    offset_.y += 10 * elapsed;
    shape_.move(offset_ * elapsed);
}

void Object::move(Direction direction, sf::Time time)
{
    auto elapsed = time.asSeconds();
    float distance = elapsed * 500;
    switch (direction)
    {
    case Direction::Down:
        shape_.move(sf::Vector2f{0, distance});
        break;
    case Direction::Up:
        shape_.move(sf::Vector2f{0, -distance});
        break;
    case Direction::Left:
        shape_.move(sf::Vector2f{-distance, 0});
        break;
    case Direction::Right:
        shape_.move(sf::Vector2f{distance, 0});
        break;
    }
}

sf::CircleShape *Object::getDrawable()
{
    return &shape_;
}