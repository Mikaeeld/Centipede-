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

/**
 * @brief Entity Manager Class
 * 
 * Acts as a container for GameEntity objects
 * Allows for creation, deletion and updates of contained objects without querying individual entities
 * Each state should contain a single entity manager
 * Also responsible for checking for collisions between included entities and calling their respective collision handlers
 * 
 */
class EntityManager
{
public:
	/**
 	* @brief Calls the tick function to update all entities contained in the entity manager
	 * 
 	* @param time time to be passed to respective tick functions
 	*/
	void tick(const sf::Time &time);

	/**
	 * @brief Creates entity of specified type at given location and adds it to the entitymanager
	 * 
	 * @param type type of entity to create
	 * @param location sfml vector containing x and y coordinates to place new entity
	 */
	void addEntity(GameEntity::entityType type, sf::Vector2f location = sf::Vector2f{0.0f, 0.0f});

	/**
	 * @brief Adds provided entity to the entitymanager
	 * 
	 * @param entity pointer to entity to add
	 */
	void addEntity(const GameEntity_ptr &entity);

	/**
	 * @brief Removes a specified entity from the entitymanager
	 * 
	 * @param entity pointer to entity to remove
	 * @return unordered_set<GameEntity_ptr>::iterator Iterator to next element in the set 
	 */
	unordered_set<GameEntity_ptr>::iterator removeEntity(const GameEntity_ptr &entity);

	/**
	 * @brief Get all entities contained in the entitymanager
	 * 
	 * @return const unordered_set<GameEntity_ptr>& Container of pointers to entities
	 */
	const unordered_set<GameEntity_ptr> &getEntities() const
	{
		return entities_;
	}

	/**
	 * @brief Get the count of a specified entity type contained in the entity manager
	 * 
	 * @param type entity type to count
	 * @return int number of entities of type contained in entity manager
	 */
	int getCount(GameEntity::entityType type);

private:
	unordered_set<GameEntity_ptr> entities_;
	map<GameEntity::entityType, int> entityCounts_;
	void checkCollisions();
	static GameEntity_ptr entityFactory(GameEntity::entityType type);
};