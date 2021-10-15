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
	Texture_ptr explode5(new sf::Texture());
	Texture_ptr explode6(new sf::Texture());
	Texture_ptr explode7(new sf::Texture());
	Texture_ptr explode8(new sf::Texture());
	Texture_ptr explode9(new sf::Texture());
	Texture_ptr explode10(new sf::Texture());
	Texture_ptr explode11(new sf::Texture());
	Texture_ptr explode12(new sf::Texture());
	Texture_ptr explode13(new sf::Texture());
	Texture_ptr explode14(new sf::Texture());
	Texture_ptr explode15(new sf::Texture());
	Texture_ptr explode16(new sf::Texture());
	Texture_ptr explode17(new sf::Texture());
	Texture_ptr explode18(new sf::Texture());

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
	if (!fire->loadFromFile(base + "ShipShooting.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode5->loadFromFile(base + "ShipDying5.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode6->loadFromFile(base + "ShipDying6.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode7->loadFromFile(base + "ShipDying7.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode8->loadFromFile(base + "ShipDying8.png"))
		throw std::runtime_error("Cannot Load Ship Image");
	if (!fire->loadFromFile(base + "ShipShooting.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode9->loadFromFile(base + "ShipDying9.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode10->loadFromFile(base + "ShipDying10.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode11->loadFromFile(base + "ShipDying11.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode12->loadFromFile(base + "ShipDying12.png"))
		throw std::runtime_error("Cannot Load Ship Image");
	if (!fire->loadFromFile(base + "ShipShooting.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode13->loadFromFile(base + "ShipDying13.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode14->loadFromFile(base + "ShipDying14.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode15->loadFromFile(base + "ShipDying15.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode16->loadFromFile(base + "ShipDying16.png"))
		throw std::runtime_error("Cannot Load Ship Image");
	if (!fire->loadFromFile(base + "ShipShooting.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode17->loadFromFile(base + "ShipDying17.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!explode18->loadFromFile(base + "ShipDying18.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	this->setPeriod(2.0);
	this->setAnimateMode(AnimateMode::loop);
	this->addKeyFrame(KeyFrame{0.0, normal});
	this->addKeyFrame(KeyFrame{10.0, fire});
	this->addKeyFrame(KeyFrame{15, explode1});
	this->addKeyFrame(KeyFrame{20, explode2});
	this->addKeyFrame(KeyFrame{25, explode3});
	this->addKeyFrame(KeyFrame{30, explode4});
	this->addKeyFrame(KeyFrame{35, explode5});
	this->addKeyFrame(KeyFrame{40, explode6});
	this->addKeyFrame(KeyFrame{45, explode7});
	this->addKeyFrame(KeyFrame{50, explode8});
	this->addKeyFrame(KeyFrame{55, explode9});
	this->addKeyFrame(KeyFrame{60, explode10});
	this->addKeyFrame(KeyFrame{65, explode11});
	this->addKeyFrame(KeyFrame{70, explode12});
	this->addKeyFrame(KeyFrame{75, explode13});
	this->addKeyFrame(KeyFrame{80, explode14});
	this->addKeyFrame(KeyFrame{85, explode15});
	this->addKeyFrame(KeyFrame{90, explode16});
	this->addKeyFrame(KeyFrame{95, explode17});
	this->addKeyFrame(KeyFrame{100, explode18});
}

void Ship::tick(sf::Time time)
{
	handleInput(time);
}

void Ship::handleInput(sf::Time time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		inputMove(Ship::Direction::Up, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		inputMove(Ship::Direction::Down, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		inputMove(Ship::Direction::Left, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		inputMove(Ship::Direction::Right, time);
	}
}

void Ship::inputMove(Direction direction, sf::Time time)
{
	auto elapsed = time.asSeconds();
	float distance = elapsed * 200;
	switch (direction)
	{
	case Direction::Down:
		move(sf::Vector2f{0, distance});
		break;
	case Direction::Up:
		move(sf::Vector2f{0, -distance});
		break;
	case Direction::Left:
		move(sf::Vector2f{-distance, 0});
		break;
	case Direction::Right:
		move(sf::Vector2f{distance, 0});
		break;
	default:
		//none
		break;
	}
}