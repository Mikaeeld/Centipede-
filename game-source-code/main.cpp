#include <SFML/Graphics.hpp>
#include "Window.h"

int main()
{

    auto window = Window("New Window", sf::Vector2u{1400, 900});
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);
    auto offset = sf::Vector2f{10, -50};
    shape.setOrigin(shape.getRadius()/2, shape.getRadius()/2);
    shape.move(sf::Vector2f{0, 900});
    while (!window.isDone())
    {
        shape.move(offset);
        offset.y += 1;

        window.update();
        window.beginDraw();
        window.draw(shape);
        window.endDraw();
    }

    return 0;
}