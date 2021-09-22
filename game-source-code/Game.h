#pragma once

#include "Window.h"

using namespace std;

class Game
{
public:
    Game();
    ~Game();

    void handleInput();
    void update();
    void render();
    Window *getWindow();

private:
    void moveBall();
    Window window_;
    sf::Vector2f offset_;
    sf::CircleShape ball_ = sf::CircleShape(100.f);
};