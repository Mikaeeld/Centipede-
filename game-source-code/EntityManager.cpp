#include "EntityManager.h"

void EntityManager::tick(sf::Time time)
{
	for (auto &entity : entities_)
	{
		if (entity->animate())
		{
			entity->animateTick(time);
		}
		entity->tick(time);
		checkCollisions();
		while (!entity->createQueue_.empty())
		{
			auto toCreate = entity->createQueue_.front();
			entity->createQueue_.pop();
			addEntity(toCreate.first, toCreate.second);
		}
		if (entity->toDelete_)
		{
			entities_.erase(entity);
		}
	}
}

// vector<Collision> EntityManager::getCollisions()
// {
// 	vector<Collision> out;
// 	for (auto a = entities_.begin(); a != entities_.end(); ++a)
// 	{
// 		for (auto b = a + 1; b != entities_.end(); ++b)
// 		{

// 			if ((*a)->collidesWith(**b))
// 			{
// 				auto collision = Collision{*a, *b};
// 				out.push_back(collision);
// 			}
// 		}
// 	}
// 	return out;
// }

// bool EntityManager::collisionMatch(const Collision &collision, const CollisionDescriptor &description)
// {
// 	if (typeExists(collision.a, description.a) && typeExists(collision.b, description.b))
// 		return true;

// 	if (typeExists(collision.b, description.a) && typeExists(collision.a, description.b))
// 		return true;

// 	return false;
// }

// bool EntityManager::typeExists(const GameEntity_ptr &entity, const string &condition)
// {
// 	auto types = (*entity).getTypes();
// 	return types.find(condition) != types.end();
// }

GameEntity_ptr EntityManager::entityFactory(GameEntity::entityType type)
{
	switch (type)
	{
	case GameEntity::entityType::Ship:
	{
		return std::make_shared<Ship>(Ship());
	}
	case GameEntity::entityType::Mushroom:
	{
		return std::make_shared<Mushroom>(Mushroom());
	}
	default:
	{
		return nullptr;
	}
	}
}

int EntityManager::addEntity(GameEntity::entityType type, sf::Vector2f location)
{
	auto entity = entityFactory(type);
	entities_.emplace(entity);
	entity->setPosition(location);
	return 1;
}

void EntityManager::removeEntity(const GameEntity_ptr &entity)
{
	auto it = entities_.find(entity);
	if (it != entities_.end())
	{
		entities_.erase(it);
	}
}

//This can be smartened up by getting all collisions, sorting them byrectanlge area in a queue and handling them
void EntityManager::checkCollisions()
{
	for (auto i : entities_)
	{
		for (auto j : entities_)
		{
			if (i != j)
			{
				sf::FloatRect rectangle;
				if (i->getGlobalBounds().intersects(j->getGlobalBounds(), rectangle))
				{
					i->handleCollision(j->getType(), rectangle);
					j->handleCollision(i->getType(), rectangle);
				}
			}
		}
	}
}