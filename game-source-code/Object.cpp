#include "Object.h"

Object::Object()
{
    shape_ = sf::CircleShape(100.0f);
    shape_.setFillColor(sf::Color::Blue);
    shape_.setOrigin(shape_.getRadius() / 2, shape_.getRadius() / 2);
    shape_.setPosition(sf::Vector2f{50, 250});
    offset_ = sf::Vector2f{0.1, -0.05};
}

Object::~Object()
{
}

void Object::update()
{
    offset_.y += 0.0001;
    shape_.move(offset_);
}

sf::CircleShape *Object::getDrawable()
{
    return &shape_;
}