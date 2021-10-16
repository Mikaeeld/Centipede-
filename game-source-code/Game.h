#pragma once

#include "GameWindow.h"
#include "ResourcePath.h"
#include "TextureManager.h"
#include "Ship.h"
#include "EntityManager.h"
#include "PlayState.h"

using namespace std;

enum class GameScene
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
    sf::Clock clock_;
    sf::Time elapsed_;
    float tickRate_;
    float frametime_;
    GameScene state_;
    sf::Sprite splash_;
    sf::Texture *splashImage_;
    TextureManager textureManager_;
    // EntityManager entityManager_;
    // sf::RectangleShape playerArea_;
    PlayState playState_;
};
