#include "Bullet.h"
#include "SFML/Graphics.hpp"
#include "ResourcePath.h"

Bullet::Bullet()
{
	Texture_ptr normal(new sf::Texture());
	const string base = resourcePath() + "Sprites/Ship/";
	if (!normal->loadFromFile(base + "Bullet.png"))
		throw std::runtime_error("Cannot Load Bullet Image");

	originAtCenter_ = true;
	addKeyFrame(KeyFrame(0.0f, normal));
	setAnimateMode(AnimateMode::pause);
}

void Bullet::tick(const sf::Time &time)
{

	auto elapsed = time.asSeconds();
	auto distance = VELOCITY * elapsed;
	move(distance);

	if (getPosition().y < MIN_Y)
	{
		toDelete_ = true;
	}
}

const sf::Vector2f Bullet::VELOCITY = sf::Vector2f{0.0f, -300.0f};