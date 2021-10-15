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

	GameEntity_ptr entityFactory(GameEntity::entityType type);
	int addEntity(GameEntity::entityType type, sf::Vector2f location = sf::Vector2f{0.0f, 0.0f});
	void removeEntity(const GameEntity_ptr &entity);

	const set<GameEntity_ptr> &getEntities() const
	{
		return entities_;
	}

private:
	set<GameEntity_ptr> entities_;
};