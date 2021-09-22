#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Game.h"

int main()
{
    Game game;
    while (!game.getWindow()->isDone())
    {
        game.update();
        game.render();
    }
    return 0;
}