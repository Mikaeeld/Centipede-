#pragma once

#include "GameWindow.h"
#include "Object.h"

using namespace std;

enum class GameState
{
    splash,
    play,
    pause
};

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
    GameState state_;
    sf::Sprite splash_;
    sf::Texture splashImage_;
    sf::Sprite ship_;
    sf::Texture shipImage_;
};
