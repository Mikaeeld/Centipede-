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

GameEntity_ptr EntityManager::addEntity(int entity)
{
	switch (entity)
	{
	case 1:
	{
		auto ship = Ship();
		auto out = std::make_shared<Ship>(ship);
		entities_.emplace(out);
		return out;
	}
	default:{
		return nullptr;
	}
	}
}

void EntityManager::removeEntity(const GameEntity_ptr &entity)
{
	auto it = entities_.find(entity);
	if (it != entities_.end())
	{
		entities_.erase(it);
	}
}