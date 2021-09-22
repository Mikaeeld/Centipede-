#pragma once

#include "SFML/Graphics.hpp"

using namespace std;

class Object
{
public:
    Object();
    ~Object();

    //This needs to return a generic drawable object
    sf::CircleShape *getDrawable();
    void tick(sf::Time time_);
private:
    sf::Vector2f offset_;
    sf::CircleShape shape_;
};