#include "PlayState.h"

PlayState::PlayState()
{
	playerArea_ = make_shared<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f{240.0f, 48.0f}));
	const sf::Color green(33, 71, 33);
	playerArea_->setFillColor(green);
	playerArea_->setPosition(0.0f, 200.0f);

	entityManager_.addEntity(GameEntity::entityType::Mushroom, sf::Vector2f{120.0f, 150.0f});

	entityManager_.addEntity(GameEntity::entityType::Ship, sf::Vector2f{120.0f, 200.0f});
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