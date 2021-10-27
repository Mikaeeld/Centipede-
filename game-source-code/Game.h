#pragma once

#include "GameWindow.h"
#include "ResourcePath.h"
#include "Ship.h"
#include "EntityManager.h"
#include "SplashState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"

using namespace std;

/**
 * @brief List of possible states in which the game can be
 *
 */
enum class GameScene
{
    splash,
    play,
    pause,
    gameOver
};

/**
 * @brief Game Class
 *
 * Basic Game engine implementaion
 * Creates and updates the render window
 * Handles game clock to ensure game objects are updated at set intervals
 * Manages and switches between game states as required
 *
 */
class Game
{
public:
    /**
     * @brief Construct a new Game object
     *
     */
    Game();

    /**
     * @brief checks for user inputs and changes gamestate accordingly
     *
     */
    void handleInput();

    /**
     * @brief Updates game and related objects based on game state
     *
     */
    void update();

    /**
     * @brief Renders the current game state to the render window
     *
     */
    void render();

    /**
     * @brief Get the Window object used by the game
     *
     * @return GameWindow*
     */
    GameWindow *getWindow();

    /**
     * @brief Get the time elapsed since the last game update tick
     *
     * @return sf::Time
     */
    sf::Time getElapsed();

    /**
     * @brief Restarts the clock, setting the elapsed time to 0
     *
     */
    void restartClock();

private:
    GameWindow window_;
    sf::Clock clock_;
    sf::Time elapsed_;
    float tickRate_;
    float frametime_;
    GameScene scene_;
    shared_ptr<SplashState> splashState_;
    shared_ptr<PlayState> playState_;
    shared_ptr<PauseState> pauseState_;
    shared_ptr<GameOverState> gameOverState_;
    shared_ptr<State> currentState_;
    shared_ptr<State> nextState_;

    void handleStateChange();
};
