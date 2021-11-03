#include <SFML/Graphics.hpp>
#include "Game.h"
#include <random>

int main()
{
    // Initialise random seed
    srand(time(0));

    Game game;
    // Terminate the process when the window is closed
    while (!game.getWindow()->isDone())
    {
        game.update();
        game.render();
        game.restartClock();
    }
    return 0;
}