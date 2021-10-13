#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include <functional>
#include <map>
using namespace std;

using GameEntity_ptr = shared_ptr<GameEntity>;

class EntityManager
{
public:
	EntityManager();

	/**
	 * @brief Calls the corresponding tick function for all animatable entities.
	 *
	 */
	void tick(sf::Time time);

	void addEntity(const GameEntity_ptr &entity);
	void removeEntity(const GameEntity_ptr &entity);

	const set<GameEntity_ptr> &getEntities() const
	{
		return entities_;
	}

private:
	set<GameEntity_ptr> entities_;
};