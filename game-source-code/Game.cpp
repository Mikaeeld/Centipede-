#include "Game.h"

Game::Game() : window_("Game", sf::Vector2u{1600, 900}), tickRate_(60.0f)
{
    frametime_ = 1.0f / tickRate_;
}

Game::~Game()
{
}

void Game::update()
{
    if (elapsed_.asSeconds() >= frametime_)
    {
        window_.update();
        object_.tick(elapsed_);
        elapsed_ -= sf::seconds(frametime_);
    }
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

sf::Time Game::getElapsed()
{
    return elapsed_;
}

void Game::restartClock()
{
    elapsed_ += clock_.restart();
}