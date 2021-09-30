#pragma once

#include "SFML/Graphics.hpp"
#include "GameEntity.h"
#include <functional>
using namespace std;

struct Collision
{
	unordered_set<string> a;
	unordered_set<string> b;
};

class EntityManager
{
public:
	EntityManager();
	// ~EntityManger();

	/**
	 * @brief Calls the corresponding tick function for all animatable entities.
	 *
	 */
	void tick(sf::Time time);

	/**
	 * @brief Checks for collisions between two entities, if one has occured then it is added to the return vector
	 *
	 * @return vector<Collision>
	 */
	vector<Collision> checkCollisions();

	/**
	 * @brief Checks if any combination from the collision matches the combination of the given conditions
	 *
	 * @param collision
	 * @param condition_a
	 * @param condition_b
	 * @return true
	 * @return false
	 */
	static bool collisionMatch(Collision &collision, const string condition_a, const string condition_b);

private:
	vector<GameEntity> entities_;
};