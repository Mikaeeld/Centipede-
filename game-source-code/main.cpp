#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Gravity!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);
    auto offset = sf::Vector2f{10, -50};
    shape.setOrigin(shape.getRadius()/2, shape.getRadius()/2);
    shape.move(sf::Vector2f{0, 900});
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        shape.move(offset);
        offset.y += 1;

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}