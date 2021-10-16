#include "PlayState.h"

PlayState::PlayState()
{
	// entityManager_ = EntityManager();

	ship_ = make_shared<Ship>(Ship());
	ship_->setPosition(sf::Vector2f{128.0f, 220.0f});

	playerArea_ = make_shared<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f{256.0f, 40.0f}));
	const sf::Color gray(100, 100, 100);
	playerArea_->setFillColor(gray);
	playerArea_->setPosition(0.0f, 200.0f);

	entityManager_.addEntity(GameEntity::entityType::Mushroom, sf::Vector2f{120.0f, 150.0f});

	entityManager_.addEntity(ship_);
}

const vector<Drawable_ptr> PlayState::getDrawable()
{
	vector<Drawable_ptr> temp;
	temp.push_back(playerArea_);
	for (auto &entity : entityManager_.getEntities())
	{
		temp.push_back(static_cast<Drawable_ptr>(entity));
	}
	return temp;
}

void PlayState::update(const sf::Time &time)
{
	entityManager_.tick(time);
}