#pragma once

#include "SFML/Graphics.hpp"

using namespace std;

class Object
{
public:
    Object();
    ~Object();

    //This needs to return a generic drawable object
    vector<sf::Drawable *> getDrawable();
    void tick(sf::Time time_);
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };
    void move(Direction direction, sf::Time time);

    void shoot();

private:
    sf::Vector2f offset_;
    sf::CircleShape shape_;

    sf::Sprite ship_;
    sf::Texture shipImage_;

    sf::Text shoot_;
    bool showShoot_;
    sf::Font shootFont_;

    const float shootTimeOut_ = 0.15;
    float shootTime_;
};