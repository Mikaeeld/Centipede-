#include "Game.h"

Game::Game() : window_("Game", sf::Vector2u{1600, 900})
{
}

Game::~Game()
{
}

void Game::update()
{
    window_.update();
    object_.update();
}

void Game::render()
{
    window_.beginDraw();
    window_.draw(*object_.getDrawable());
    window_.endDraw();
}

Window *Game::getWindow()
{
    return &window_;
}

void Game::handleInput()
{
}