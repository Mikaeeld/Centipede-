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
	virtual void update(const sf::Time &time);

	/**
	 * @brief Get all drawable objects contained in the state
	 *
	 * @return const vector<Drawable_ptr>
	 */
	virtual const vector<Drawable_ptr> getDrawable();

	State();

	virtual void handleInput();

	virtual void reset();

	const bool &renderWithAbove() const;
	const bool &renderBelow() const;
	const bool &nextState() const;
	const bool &exit() const;

protected:
	EntityManager entityManager_;
	bool renderWithAbove_;
	bool renderBelow_;
	bool nextState_;
	bool exit_;
};