#pragma once

#include <functional>
#include <map>
#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include "Ship.h"
#include "Mushroom.h"
#include "Bullet.h"

using namespace std;

using GameEntity_ptr = shared_ptr<GameEntity>;

class EntityManager
{
public:
	/**
	 * @brief Calls the corresponding tick function for all animatable entities.
	 *
	 */
	void tick(const sf::Time &time);

	static GameEntity_ptr entityFactory(GameEntity::entityType type);
	int addEntity(GameEntity::entityType type, sf::Vector2f location = sf::Vector2f{0.0f, 0.0f});
	int addEntity(const GameEntity_ptr &entity);
	void removeEntity(const GameEntity_ptr &entity);
	void checkCollisions();

	const set<GameEntity_ptr> &getEntities() const
	{
		return entities_;
	}

private:
	set<GameEntity_ptr> entities_;
};