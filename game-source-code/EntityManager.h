#pragma once

#include <functional>
#include <map>
#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include "Ship.h"

using namespace std;

using GameEntity_ptr = shared_ptr<GameEntity>;

class EntityManager
{
public:

	/**
	 * @brief Calls the corresponding tick function for all animatable entities.
	 *
	 */
	void tick(sf::Time time);

	GameEntity_ptr addEntity(int entity);
	void removeEntity(const GameEntity_ptr &entity);

	const set<GameEntity_ptr> &getEntities() const
	{
		return entities_;
	}

private:
	set<GameEntity_ptr> entities_;
};