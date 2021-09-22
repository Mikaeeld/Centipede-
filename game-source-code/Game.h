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

private:
    Window window_;
    Object object_;
};