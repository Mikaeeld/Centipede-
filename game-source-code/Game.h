#pragma once

#include "GameWindow.h"
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
    GameWindow *getWindow();
    sf::Time getElapsed();
    void restartClock();

private:
    GameWindow window_;
    Object object_;
    sf::Clock clock_;
    sf::Time elapsed_;
    float tickRate_;
    float frametime_;
};
