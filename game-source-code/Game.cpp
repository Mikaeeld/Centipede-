#include "Game.h"

Game::Game() : window_("Game", sf::Vector2u{800, 600}, 120), tickRate_(240.0f)
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
        handleInput();
        window_.update();
        //object_.tick(elapsed_);
        elapsed_ = sf::seconds(0.0);
    }
}

void Game::render()
{
    window_.beginDraw();
    window_.draw(*object_.getDrawable());
    window_.endDraw();
}

GameWindow *Game::getWindow()
{
    return &window_;
}

void Game::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        object_.move(Object::Direction::Up, elapsed_);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        object_.move(Object::Direction::Down, elapsed_);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        object_.move(Object::Direction::Left, elapsed_);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        object_.move(Object::Direction::Right, elapsed_);
    }
}

sf::Time Game::getElapsed()
{
    return elapsed_;
}

void Game::restartClock()
{
    elapsed_ += clock_.restart();
}
