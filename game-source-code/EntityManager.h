#pragma once

#include <functional>
#include <map>
#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include "Ship.h"
#include "Mushroom.h"
#include "Bullet.h"
#include "DDT.h"
#include "Explosion.h"
#include "CentipedeSegment.h"
#include "Spider.h"

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

	int addEntity(GameEntity::entityType type, sf::Vector2f location = sf::Vector2f{0.0f, 0.0f});
	int addEntity(const GameEntity_ptr &entity);
	unordered_set<GameEntity_ptr>::iterator removeEntity(const GameEntity_ptr &entity);

	const unordered_set<GameEntity_ptr> &getEntities() const
	{
		return entities_;
	}

	int getCount(GameEntity::entityType type);

private:
	unordered_set<GameEntity_ptr> entities_;
	map<GameEntity::entityType, int> entityCounts_;
	void checkCollisions();
	static GameEntity_ptr entityFactory(GameEntity::entityType type);
};