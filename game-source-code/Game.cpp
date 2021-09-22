#include "Game.h"

Game::Game() : window_("Game", sf::Vector2u{1600, 900})
{
    ball_.setFillColor(sf::Color::Blue);
    offset_ = sf::Vector2f{0.1, -0.05};
    ball_.setOrigin(ball_.getRadius() / 2, ball_.getRadius() / 2);
    ball_.setPosition(sf::Vector2f{50, 250});
}

Game::~Game()
{
}

void Game::update()
{
    window_.update();
    moveBall();
}

void Game::moveBall()
{
    offset_.y += 0.0001;
    ball_.move(offset_);
}

void Game::render()
{
    window_.beginDraw();
    window_.draw(ball_);
    window_.endDraw();
}

Window *Game::getWindow()
{
    return &window_;
}

void Game::handleInput() {
    
}