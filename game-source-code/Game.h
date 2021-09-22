#pragma once

#include "Window.h"
#include "Object.h"

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
    sf::Time getElapsed();
    void restartClock();

private:
    Window window_;
    Object object_;
    sf::Clock clock_;
    sf::Time elapsed_;
    float tickRate_;
    float frametime_;
};