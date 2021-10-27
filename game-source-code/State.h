#pragma once
#include "SFML/Graphics.hpp"
#include "EntityManager.h"
#include "GameEntity.h"

using Drawable_ptr = shared_ptr<sf::Drawable>;

/**
 * @brief Base State class
 * 
 * The base for gameplay states
 * Contains entities of state and can be updated as required
 * 
 */
class State
{

public:

	/**
	 * @brief Updates the state and entities contained within
	 * 
	 * @param time 
	 */
	virtual void update(const sf::Time &time)
	{
		(void)time;
	};

	/**
	 * @brief Get all drawable objects contained in the state
	 * 
	 * @return const vector<Drawable_ptr> 
	 */
	virtual const vector<Drawable_ptr> getDrawable()
	{
		vector<Drawable_ptr> out(entityManager_.getEntities().size());
		for (auto &entity : entityManager_.getEntities())
		{
			if (auto temp = dynamic_pointer_cast<sf::Drawable>(entity))
				out.push_back(temp);
		}
		return out;
	}

protected:
	EntityManager entityManager_;
};