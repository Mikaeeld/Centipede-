#include "PlayState.h"

PlayState::PlayState()
{
	playerArea_ = make_shared<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f{240.0f, 48.0f}));
	const sf::Color green(33, 71, 33);
	playerArea_->setFillColor(green);
	playerArea_->setPosition(0.0f, 200.0f);

	for (float i = 8.0f; i <= 224.0f; i += 8.0f)
	{
		for (float j = 8.0f; j <= 232.f; j += 8.f)
		{
			auto trial = (j >= GameGrid::PLAYER_AREA_Y_MIN) ? 0.04 : 0.1;

			if (randomBool(trial))
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
		spawnDDT(time);
		spawnSpider(time);
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

void PlayState::spawnDDT(const sf::Time &time)
{
	ddtSpawnTime_ -= time.asSeconds();
	if (ddtSpawnTime_ < 0)
	{
		ddtSpawnTime_ = 3.0f;
		if (entityManager_.getCount(GameEntity::entityType::DDT) < 4 && randomBool())
		{
			float x = randomInt(0, 28) * 8 + 8;
			float y = randomInt(0, 20) * 8 + 4;
			entityManager_.addEntity(GameEntity::entityType::DDT, sf::Vector2f{x, y});
		}
	}
}

void PlayState::spawnSpider(const sf::Time &time)
{
	spiderSpawnTime_ -= time.asSeconds();
	if (spiderSpawnTime_ < 0)
	{
		spiderSpawnTime_ = 3.0f;
		if (randomBool())
		{
			float x = int(randomBool()) * 256 - 8;
			float y = randomInt(20, 30) * 8 + 4;
			entityManager_.addEntity(GameEntity::entityType::Spider, sf::Vector2f{x, y});
		}
	}
}