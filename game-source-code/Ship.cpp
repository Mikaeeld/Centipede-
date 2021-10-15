#include "Ship.h"
#include "SFML/Graphics.hpp"

Ship::Ship()
{
	// Initialize Key Frames
	Texture_ptr normal(new sf::Texture());
	Texture_ptr fire(new sf::Texture());
	Texture_ptr explode1(new sf::Texture());
	Texture_ptr explode2(new sf::Texture());
	Texture_ptr explode3(new sf::Texture());
	Texture_ptr explode4(new sf::Texture());

	const string base = "Sprites/Ship/";

	if (!normal->loadFromFile(base + "Ship.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!fire->loadFromFile(base + "ShipShooting.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode1->loadFromFile(base + "ShipDying1.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode2->loadFromFile(base + "ShipDying2.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode3->loadFromFile(base + "ShipDying3.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode4->loadFromFile(base + "ShipDying4.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	this->setPeriod(1.0);
	this->setAnimateMode(AnimateMode::loop);
	this->addKeyFrame(KeyFrame{0.0, normal});
	this->addKeyFrame(KeyFrame{20.0, fire});
	this->addKeyFrame(KeyFrame{50, explode1});
	this->addKeyFrame(KeyFrame{60, explode2});
	this->addKeyFrame(KeyFrame{70, explode3});
	this->addKeyFrame(KeyFrame{80, explode4});

	this->setScale(5, 5);
}

void Ship::inputMove(Direction direction, sf::Time time)
{
	auto elapsed = time.asSeconds();
	float distance = elapsed * 500;
	switch (direction)
	{
	case Direction::Down:
		move(sf::Vector2f{0, distance});
		move(sf::Vector2f{0, distance});
		break;
	case Direction::Up:
		move(sf::Vector2f{0, -distance});
		move(sf::Vector2f{0, -distance});
		break;
	case Direction::Left:
		move(sf::Vector2f{-distance, 0});
		move(sf::Vector2f{-distance, 0});
		break;
	case Direction::Right:
		move(sf::Vector2f{distance, 0});
		move(sf::Vector2f{distance, 0});
		break;
	default:
		//none
		break;
	}
}