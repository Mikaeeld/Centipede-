#pragma once

#include "SFML/Graphics.hpp"

using namespace std;

class Object
{
public:
    Object();
    ~Object();

    void update();
    //This needs to return a generic drawable object
    sf::CircleShape *getDrawable();

private:
    sf::Vector2f offset_;
    sf::CircleShape shape_;
};