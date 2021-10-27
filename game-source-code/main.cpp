#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game game;
    //Terminate the process when the window is closed
    while (!game.getWindow()->isDone())
    {
        game.update();
        game.render();
        game.restartClock();
    }
    return 0;
}