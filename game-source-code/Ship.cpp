#include "Ship.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

Ship::Ship()
{
	originAtCenter_ = true;
	reload_ = 0.0f;
	// Initialize Key Frames
	Texture_ptr normal(new sf::Texture());
	Texture_ptr fire(new sf::Texture());

	const string base = resourcePath() + "Sprites/Ship/";

	if (!normal->loadFromFile(base + "Ship.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	if (!fire->loadFromFile(base + "ShipShooting.png"))
		throw std::runtime_error("Cannot Load Ship Image");

	this->addKeyFrame(KeyFrame{0.1f, normal});
	this->addKeyFrame(KeyFrame{1.0f, fire});

	for (int i = 1; i <= 18; i++)
	{
		Texture_ptr explodeFrame(new sf::Texture);

		if (!explodeFrame->loadFromFile(base + "ShipDying" + to_string(i) + ".png"))
			throw std::runtime_error("Cannot Load Ship Image");

		this->addKeyFrame(KeyFrame{15.0f + ((i - 1) * 5.0f), explodeFrame});
	}

	this->setPeriod(1.5f);
	this->setAnimateMode(AnimateMode::pause);
	this->dynamic_ = true;
	condition_ = Condition::Alive;
}

void Ship::tick(const sf::Time &time)
{
	if (condition_ == Condition::Alive)
	{
		handleInput(time);
		checkBounds();

		if (reload_ > 0)
		{
			reload_ -= time.asSeconds();
		}
		else if (reload_ < 0)
		{
			reload_ = 0;
			normal();
		}
	}

	if (condition_ == Condition::Dying)
	{
		if (animateDone())
		{
			toDelete_ = true;
		}
	}
}

void Ship::fire()
{
	if (reload_ <= 0.0f)
	{
		createQueue_.push(pair<GameEntity::entityType, sf::Vector2f>{GameEntity::entityType::Bullet, sf::Vector2f{getPosition().x, getPosition().y - 3.0f}});
		this->setAnimateStart(10.0f);
		this->setAnimateMode(AnimateMode::pause);
		reload_ = 0.2f;
	}
}

void Ship::normal()
{
	this->setAnimateStart(0.0f);
	this->setAnimateMode(AnimateMode::pause);
}

void Ship::explode()
{
	condition_ = Condition::Dying;
	this->setAnimateEnd(100.0f);
	this->setAnimateStart(15.0f);
	this->setAnimateMode(AnimateMode::once);
}

void Ship::handleInput(sf::Time time)
{

	if (condition_ == Condition::Alive)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			fire();
		}
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

bool Ship::handleCollision(entityType type, sf::FloatRect collisionRect)
{
	switch (type)
	{
	case entityType::Mushroom:
	{
		switch (direction_)
		{
		case Direction::Down:
			this->move(sf::Vector2f(0.0f, -collisionRect.height));
			break;
		case Direction::Up:
			this->move(sf::Vector2f(0.0f, collisionRect.height));
			break;
		case Direction::Left:
			this->move(sf::Vector2f(collisionRect.width, 0.0f));
			break;
		case Direction::Right:
			this->move(sf::Vector2f(-collisionRect.width, 0.0f));
			break;
		default:
			// none
			break;
		}
		break;
	}
	case entityType::CentipedeSegment:
	{
		explode();
		break;
	}
	default:
	{
		return false;
		break;
	}
	}

	return true;
}

void Ship::inputMove(Direction direction, sf::Time time)
{
	auto elapsed = time.asSeconds();
	float distance = elapsed * 150;
	switch (direction)
	{
	case Direction::Down:
		move(sf::Vector2f{0, distance});
		direction_ = Direction::Down;
		break;
	case Direction::Up:
		move(sf::Vector2f{0, -distance});
		direction_ = Direction::Up;
		break;
	case Direction::Left:
		move(sf::Vector2f{-distance, 0});
		direction_ = Direction::Left;
		break;
	case Direction::Right:
		move(sf::Vector2f{distance, 0});
		direction_ = Direction::Right;
		break;
	default:
		// none
		break;
	}
}