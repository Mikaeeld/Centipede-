#include "Window.h"

Window::Window() : Window("New Window", sf::Vector2u(1024, 768))
{
}

Window::Window(const string &title, const sf::Vector2u &size) : Window(title, size, 0)
{
}

Window::Window(const string &title, const sf::Vector2u &size, int framerate) : framerateLimit_{framerate}
{
    setup(title, size);
}

Window::~Window()
{
    destroy();
}

void Window::setup(const string title, const sf::Vector2u size)
{
    title_ = title;
    size_ = size;
    isFullscreen_ = false;
    isDone_ = false;
    create();
}

void Window::create()
{
    auto style = (isFullscreen_ ? sf::Style::Fullscreen : sf::Style::Default);
    window_.create(sf::VideoMode{size_.x, size_.y, 32}, title_, style);
    if (framerateLimit_ != 0)
    {
        window_.setFramerateLimit(framerateLimit_);
    }
}

void Window::destroy()
{
    window_.close();
}

void Window::update()
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

void Window::toggleFullscreen()
{
    isFullscreen_ = !isFullscreen_;
    destroy();
    create();
}

void Window::beginDraw()
{
    window_.clear(sf::Color::Black);
}

void Window::endDraw()
{
    window_.display();
}

bool Window::isDone()
{
    return isDone_;
}

bool Window::isFullscreen()
{
    return isFullscreen_;
}

sf::Vector2u Window::getSize()
{
    return size_;
}

void Window::draw(sf::Drawable &drawable)
{
    window_.draw(drawable);
}