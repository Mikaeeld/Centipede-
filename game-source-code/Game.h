#pragma once

#include "GameWindow.h"
#include "ResourcePath.h"
#include "Ship.h"
#include "EntityManager.h"
#include "PlayState.h"

using namespace std;

enum class GameScene
{
    splash,
    play,
    pause,
    gameOver
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
    sf::Clock clock_;
    sf::Time elapsed_;
    float tickRate_;
    float frametime_;
    GameScene state_;
    sf::Sprite splash_;
    shared_ptr<sf::Texture> splashImage_;
    sf::Sprite gameover_;
    shared_ptr<sf::Texture> gameoverImage_;
    sf::Sprite paused_;
    shared_ptr<sf::Texture> pausedImage_;
    PlayState playState_;
};
