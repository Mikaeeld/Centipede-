#include "GameWindow.h"

GameWindow::GameWindow() : GameWindow("New Window", sf::Vector2u(1024, 768))
{
}

GameWindow::GameWindow(const string &title, const sf::Vector2u &size) : GameWindow(title, size, 0)
{
}

GameWindow::GameWindow(const string &title, const sf::Vector2u &size, int framerate) : framerateLimit_{framerate}
{
    setup(title, size);
}

GameWindow::~GameWindow()
{
    destroy();
}

void GameWindow::setup(const string title, const sf::Vector2u size)
{
    title_ = title;
    size_ = size;
    isFullscreen_ = false;
    isDone_ = false;
    create();
}

void GameWindow::create()
{
    auto style = (isFullscreen_ ? sf::Style::Fullscreen : sf::Style::Default);
    window_.create(sf::VideoMode{size_.x, size_.y, 32}, title_, style);
    if (framerateLimit_ != 0)
    {
        window_.setFramerateLimit(framerateLimit_);
    }
}

void GameWindow::destroy()
{
    window_.close();
}

void GameWindow::update()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            isDone_ = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
        {
            toggleFullscreen();
        }
    }
}

void GameWindow::toggleFullscreen()
{
    isFullscreen_ = !isFullscreen_;
    destroy();
    create();
}

void GameWindow::close() {
    isDone_ = true;
}

void GameWindow::beginDraw()
{
    window_.clear(sf::Color::Black);
}

void GameWindow::endDraw()
{
    window_.display();
}

bool GameWindow::isDone()
{
    return isDone_;
}

bool GameWindow::isFullscreen()
{
    return isFullscreen_;
}

sf::Vector2u GameWindow::getSize()
{
    return size_;
}

void GameWindow::draw(sf::Drawable &drawable)
{
    window_.draw(drawable);
}