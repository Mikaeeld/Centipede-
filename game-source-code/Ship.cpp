#include "Ship.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

Ship::Ship()
{
	originAtCenter_ = true;
	// Initialize Key Frames
	Texture_ptr normal(new sf::Texture());
	Texture_ptr fire(new sf::Texture());

	const string base = resourcePath() + "Sprites/Ship/";

	if (!normal->loadFromFile(base + "Ship.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!fire->loadFromFile(base + "ShipShooting.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	this->addKeyFrame(KeyFrame{0.0, normal});
	this->addKeyFrame(KeyFrame{1.0, fire});

	for (int i = 1; i <= 18; i++)
	{
		Texture_ptr explodeFrame(new sf::Texture);

		if (!explodeFrame->loadFromFile(base + "ShipDying" + to_string(i) + ".png"))
			throw std::runtime_error("Cannot Load Ship Image");

		this->addKeyFrame(KeyFrame{15.0f + ((i - 1) * 5.0f), explodeFrame});
	}

	this->setPeriod(1.5f);
	this->setAnimateMode(AnimateMode::loop);

	this->setAnimateMode(AnimateMode::pause);
}

void Ship::tick(sf::Time time)
{
	handleInput(time);
	checkBounds();
}

void Ship::fire()
{
	this->setAnimateStart(0.0f);
	this->setAnimateEnd(14.0f);
	this->setAnimateMode(AnimateMode::once_restart);
}

void Ship::normal()
{
	this->setAnimateStart(0.0f);
	this->setAnimateMode(AnimateMode::pause);
}

void Ship::explode()
{
	this->setAnimateEnd(100.0f);
	this->setAnimateStart(15.0f);
	this->setAnimateMode(AnimateMode::once);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		createQueue_.emplace(pair<GameEntity::entityType, sf::Vector2f>{GameEntity::entityType::Mushroom, sf::Vector2f{getPosition().x, getPosition().y}});
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		fire();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		explode();
	}
}

void Ship::checkBounds()
{
	auto current = this->getPosition();

	if (current.x > MAX_X)
	{
		this->setPosition(MAX_X, current.y);
	}
	else if (current.x < MIN_X)
	{
		this->setPosition(MIN_X, current.y);
	}
	current = this->getPosition();

	if (current.y > MAX_Y)
	{
		this->setPosition(current.x, MAX_Y);
	}
	else if (current.y < MIN_Y)
	{
		this->setPosition(current.x, MIN_Y);
	}
}

GameEntity::entityType Ship::getType()
{
	return GameEntity::entityType::Ship;
}

void Ship::inputMove(Direction direction, sf::Time time)
{
	auto elapsed = time.asSeconds();
	float distance = elapsed * 150;
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
		// none
		break;
	}
}