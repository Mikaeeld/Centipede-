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
    view_ = sf::View(sf::FloatRect(0.0f, 0.0f, 256.0f, 240.0f));
    viewBackground_ = sf::RectangleShape(sf::Vector2f(view_.getSize().x, view_.getSize().y));
    viewBackground_.setFillColor(sf::Color::Black);
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
    isBorderless_ = false;
    isDone_ = false;
    create();
}

void GameWindow::create()
{
    auto style = (isFullscreen_ ? sf::Style::Fullscreen : sf::Style::Default);
    if (isBorderless_ && !isFullscreen_)
    {
        style = sf::Style::None;
    }
    window_.create(sf::VideoMode{size_.x, size_.y, 32}, title_, style);
    if (framerateLimit_ != 0)
    {
        window_.setFramerateLimit(framerateLimit_);
    }
    window_.clear(sf::Color::Red);
    window_.setView(view_);
    fixAspectRatio();
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
        if (event.type == sf::Event::Resized)
        {
            size_ = sf::Vector2u(event.size.width, event.size.height);
            fixAspectRatio();
        }
    }
}

void GameWindow::fixAspectRatio()
{
    auto aspectRatioWindow = float(size_.x) / float(size_.y);
    auto aspectRatioView = float(view_.getSize().x) / float(view_.getSize().y);
    // if window is wider than view then fit vertical dimension
    if (aspectRatioWindow >= aspectRatioView)
    {
        auto xFactor = (aspectRatioWindow - aspectRatioView) / aspectRatioWindow;
        view_.setViewport(sf::FloatRect(xFactor / 2, 0.0f, 1 - xFactor, 1.0f));
    }
    else
    {
        auto yFactor = (aspectRatioView - aspectRatioWindow) / aspectRatioView;
        view_.setViewport(sf::FloatRect(0.0f, yFactor / 2, 1.0f, 1 - yFactor));
    }
    window_.setView(view_);
}

void GameWindow::toggleFullscreen()
{
    isFullscreen_ = !isFullscreen_;
    destroy();
    create();
}

void GameWindow::toggleBorderless()
{
    isBorderless_ = !isBorderless_;
    destroy();
    create();
}

void GameWindow::close()
{
    isDone_ = true;
}

void GameWindow::beginDraw()
{
    window_.clear(sf::Color::White);
    window_.draw(viewBackground_);
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

sf::View GameWindow::getView()
{
    return view_;
}

void GameWindow::draw(sf::Drawable &drawable)
{
    window_.draw(drawable);
}