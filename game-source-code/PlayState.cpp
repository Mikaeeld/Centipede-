#include "PlayState.h"

PlayState::PlayState()
{
	playerArea_ = make_shared<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f{240.0f, 48.0f}));
	const sf::Color green(33, 71, 33);
	playerArea_->setFillColor(green);
	playerArea_->setPosition(0.0f, 200.0f);

	// entityManager_.addEntity(GameEntity::entityType::Ship, sf::Vector2f{120.0f, 200.0f});
	entityManager_.addEntity(GameEntity::entityType::DDT, sf::Vector2f{120.0f, 80.0f});

	for (float i = 8.0f; i <= 224.0f; i += 8.0f)
	{
		for (float j = 8.0f; j <= 232.f; j += 8.f)
		{
			auto trial = (j >= GameGrid::PLAYER_AREA_Y_MIN) ? 0.04 : 0.1;

			if (binomial_trial(trial))
			{
				entityManager_.addEntity(GameEntity::entityType::Mushroom, sf::Vector2f{i, j});
			}
		}
	}

	centipedeSpeed_ = Speed_ptr(new float(100.0f));
	centipede_ = Centipede(entityManager_, centipedeSpeed_);

	ship_ = shared_ptr<Ship>(new Ship());
	ship_->setPosition(120.0f, 200.0f);

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
	if (ship_->getCondition() == Ship::Condition::Alive)
	{
		entityManager_.tick(time);
		if (entityManager_.getCount(GameEntity::entityType::Ship) == 0 || entityManager_.getCount(GameEntity::entityType::CentipedeSegment) == 0)
		{
			toDelete_ = true;
		}
	}
	else
	{
		if (ship_->animateDone())
		{
			toDelete_ = true;
		}
		else
		{
			ship_->animateTick(time);
		}
	}
}