#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
/**
 * @brief Game Window class
 * 
 * Wrapper for the SFML window class.
 * Provides functions for rendering and managing the render window
 * Handles resizing, ensuring a constant game area is kept and aspect ratio is maintained
 * Enforces maximum window size
 * 
 */
class GameWindow
{
public:
    /**
     * @brief Construct a new Game Window object
     * 
     */
    GameWindow();

    /**
     * @brief Construct a new Game Window object with a given title and window size
     * 
     * @param title Title of window
     * @param size Size of window
     */
    GameWindow(const string &title, const sf::Vector2u &size);

    /**
     * @brief Construct a new Game Window object with a given title, size and framerate
     * 
     * @param title Title of window
     * @param size Size of window
     * @param framerate Framerate limit of associated window, using SFML default framerate limiter, 0 for none
     */
    GameWindow(const string &title, const sf::Vector2u &size, int framerate);
    ~GameWindow();

    /**
     * @brief Clears the render window
     * 
     */
    void beginDraw();

    /**
     * @brief Ends the render cycle and outputs the framebuffer to the display
     * 
     */
    void endDraw();

    /**
     * @brief Polls or input and OS level window events and updates window state accordingly
     * 
     */
    void update();

    /**
     * @brief Check if window is set to be closed in the next update loop
     * 
     * @return true 
     * @return false 
     */
    bool isDone();

    /**
     * @brief Check if window is in fulscreen or not
     * 
     * @return true 
     * @return false 
     */
    bool isFullscreen();

    /**
     * @brief Get the Size of the window
     * 
     * @return sf::Vector2u 
     */
    sf::Vector2u getSize();

    /**
     * @brief Get the SFML View used by the window. This is the area that is actually displayed on screen and is scaled to fit the window
     * 
     * @return sf::View 
     */
    sf::View getView();

    /**
     * @brief Toggles fullscreen mode of the window
     * 
     */
    void toggleFullscreen();

    /**
     * @brief Toggles borderless window mode (titlebar and window controls are hidden)
     * 
     */
    void toggleBorderless();

    /**
     * @brief Sets the window to be closed in the next update loop
     * 
     */
    void close();

    /**
     * @brief Draws the given object to the window framebuffer
     * 
     * @param drawable SFML drawable object
     */
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