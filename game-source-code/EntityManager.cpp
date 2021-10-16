#include "EntityManager.h"

#include <iostream>
void EntityManager::tick(const sf::Time &time)
{

	for (auto &entity : entities_)
	{
		if (entity->animate())
		{
			entity->animateTick(time);
		}
		entity->tick(time);
		// checkCollisions();
		while (!entity->createQueue_.empty())
		{
			auto toCreate = entity->createQueue_.front();
			entity->createQueue_.pop();
			addEntity(toCreate.first, toCreate.second);
		}
		if (entity->toDelete_)
		{
			entities_.erase(find(entities_.begin(), entities_.end(), entity));
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
	default:
	{
		throw runtime_error("Invalid Entity Type in Factory");
	}
	}
}

int EntityManager::addEntity(GameEntity::entityType type, sf::Vector2f location)
{
	auto entity = entityFactory(type);
	addEntity(entity);
	entity->setPosition(location);
	return 1;
}

int EntityManager::addEntity(const GameEntity_ptr &entity)
{

	entities_.insert(entity);
	return 1;
}

void EntityManager::removeEntity(const GameEntity_ptr &entity)
{
	auto it = find(entities_.begin(), entities_.end(), entity);
	if (it != entities_.end())
	{
		entities_.erase(it);
	}
}

// This can be smartened up by getting all collisions, sorting them byrectanlge area in a queue and handling them
void EntityManager::checkCollisions()
{
	for (auto i = entities_.begin(); i != entities_.end(); ++i)
	{
		auto j = i;
		j++;
		for (; j != entities_.end(); ++j)
		{
			sf::FloatRect rectangle;
			if ((*i)->collidesWith(**j, rectangle))
			{
				(*i)->handleCollision((*j)->getType(), rectangle);
				(*j)->handleCollision((*i)->getType(), rectangle);
			}
		}
	}
}