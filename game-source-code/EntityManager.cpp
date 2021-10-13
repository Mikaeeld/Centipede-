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

void EntityManager::addEntity(const GameEntity_ptr &entity)
{
	entities_.insert(entity);
}

void EntityManager::removeEntity(const GameEntity_ptr &entity)
{
	auto it = entities_.find(entity);
	if (it != entities_.end())
	{
		entities_.erase(it);
	}
}