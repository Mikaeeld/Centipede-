#include "EntityManager.h"

#include <iostream>

void EntityManager::tick(const sf::Time &time)
{
	// auto it = entities_.begin();
	// while (it != entities_.end())
	// {
	// 	auto entity = *it;
	// 	if (entity->toDelete())
	// 	{
	// 		auto itTemp = it;
	// 		it = removeEntity(*itTemp);
	// 		continue;
	// 	}
	// 	else
	// 	{
	// 		++it++;
	// 	}
	// }

	set<GameEntity_ptr> toRemove;

	for (auto &entity : entities_)
	{
		while (!entity->createQueue_.empty())
		{
			auto toCreate = entity->createQueue_.front();
			entity->createQueue_.pop();
			addEntity(toCreate.first, toCreate.second);
		}
		if (entity->toDelete())
			toRemove.insert(entity);
	}

	for (auto &remove : toRemove)
		removeEntity(remove);

	for (auto &entity : entities_)
	{
		if (entity->toDelete())
		{
			toRemove.insert(entity);
		}

		if (entity->animate())
		{
			entity->animateTick(time);
		}
		entity->tick(time);
	}

	checkCollisions();
}

GameEntity_ptr EntityManager::entityFactory(GameEntity::entityType type)
{
	switch (type)
	{
	case GameEntity::entityType::Ship:
	{
		return shared_ptr<Ship>(new Ship());
	}

	case GameEntity::entityType::Mushroom:
	{
		return shared_ptr<Mushroom>(new Mushroom());
	}

	case GameEntity::entityType::Bullet:
	{
		return shared_ptr<Bullet>(new Bullet());
	}
	case GameEntity::entityType::DDT:
	{
		return shared_ptr<DDT>(new DDT());
	}
	case GameEntity::entityType::Explosion:
	{
		return shared_ptr<Explosion>(new Explosion());
	}
	default:
	{
		throw runtime_error("Invalid Entity Type in Factory");
	}
	}
}

int EntityManager::addEntity(GameEntity::entityType type, sf::Vector2f location)
{
	auto entity = entityFactory(type);

	entities_.insert(entity);
	entity->setPosition(location);
	if (entityCounts_.find(type) == entityCounts_.end())
	{
		entityCounts_.insert(std::pair<GameEntity::entityType, int>(type, 0));
	}
	entityCounts_.find(type)->second++;
	return 1;
}

int EntityManager::addEntity(const GameEntity_ptr &entity)
{

	entities_.insert(entity);
	auto type = entity->getType();
	if (entityCounts_.find(type) == entityCounts_.end())
	{
		entityCounts_.insert(std::pair<GameEntity::entityType, int>(type, 0));
	}
	entityCounts_.find(type)->second++;
	return 1;
}

set<GameEntity_ptr>::iterator EntityManager::removeEntity(const GameEntity_ptr &entity)
{
	auto type = entity->getType();
	auto it = entities_.find(entity);
	if (it != entities_.end())
	{
		it = entities_.erase(it);
	}
	entityCounts_.find(type)->second--;
	return it;
}

// This can be smartened up by getting all collisions, sorting them byrectanlge area in a queue and handling them
void EntityManager::checkCollisions()
{

	// for (auto entity : entities_)
	// {
	// 	if (entity->isDynamic())
	// 	{
	// 		for (auto entity2 : entities_)
	// 		{
	// 			sf::FloatRect rectangle;
	// 			if (entity != entity2 && entity->getGlobalBounds().intersects(entity2->getGlobalBounds(), rectangle))
	// 			{
	// 				entity->handleCollision(entity2->getType(), rectangle);
	// 				entity2->handleCollision(entity->getType(), rectangle);
	// 			}
	// 		}
	// 	}
	// }

	set<GameEntity_ptr> dynamicEntities;

	for (auto entity : entities_)
	{
		if (entity->isDynamic())
		{
			dynamicEntities.insert(entity);
			for (auto entity2 : entities_)
			{
				if (!entity2->isDynamic())
				{
					sf::FloatRect rectangle;
					if (entity != entity2 && entity->getGlobalBounds().intersects(entity2->getGlobalBounds(), rectangle))
					{
						auto c1 = entity->handleCollision(entity2->getType(), rectangle);
						auto c2 = entity2->handleCollision(entity->getType(), rectangle);
						if (c1 || c2)
						{
							goto nextEntity; // one collision only
							dynamicEntities.erase(entity);
						}
					}
				}
			}
		}

	nextEntity:;
	}

	// Check dynamic entity colliding with another dynamic entity
	for (auto i = dynamicEntities.begin(); i != dynamicEntities.end(); ++i)
	{
		auto entity = *i;
		auto j = i;
		j++;
		for (; j != dynamicEntities.end(); ++j)
		{
			auto entity2 = *j;
			sf::FloatRect rectangle;
			if (entity->getGlobalBounds().intersects(entity2->getGlobalBounds(), rectangle))
			{
				auto c1 = entity->handleCollision(entity2->getType(), rectangle);
				auto c2 = entity2->handleCollision(entity->getType(), rectangle);
				if (c1 || c2)
					goto nextDynamic; // one collision only
			}
		}
	nextDynamic:;
	}
}

int EntityManager::getCount(GameEntity::entityType type)
{
	return entityCounts_.find(type)->second;
}