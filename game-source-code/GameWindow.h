#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class GameWindow
{
public:
    GameWindow();
    GameWindow(const string &title, const sf::Vector2u &size);
    GameWindow(const string &title, const sf::Vector2u &size, int framerate);
    ~GameWindow();

    void beginDraw();
    void endDraw();

    void update();

    bool isDone();
    bool isFullscreen();
    sf::Vector2u getSize();
    sf::View getView();

    void toggleFullscreen();
    void toggleBorderless();
    void close();

    void draw(sf::Drawable &drawable);

private:
    void setup(const string title, const sf::Vector2u size);
    void destroy();
    void create();
    void fixAspectRatio();

    sf::RenderWindow window_;
    sf::Vector2u size_;
    sf::View view_;
    sf::RectangleShape viewBackground_;
    string title_;
    bool isDone_;
    bool isFullscreen_;
    bool isBorderless_;
    int framerateLimit_;
};