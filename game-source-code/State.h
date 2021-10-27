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

	/**
	 * @brief Construct a new State object
	 *
	 */
	State();

	/**
	 * @brief Handles user input
	 *
	 * To be defined when inherited, otherwise does nothing by default
	 *
	 */
	virtual void handleInput();

	/**
	 * @brief Resets the state of important variables: nextSate_ & exit_
	 *
	 */
	virtual void reset();

	/**
	 * @brief Returns the value of the 'renderWithAbove' flag
	 *
	 * If true the state requests to be rendered under the currently active state
	 * @return true
	 * @return false
	 */
	const bool &renderWithAbove() const;

	/**
	 * @brief Returns the value of the 'renderBelow' flag
	 *
	 * If true the state allows for the state beneath to be rendered with it
	 * @return true
	 * @return false
	 */
	const bool &renderBelow() const;

	/**
	 * @brief Returns the value of the 'nextState' flag
	 *
	 * If true the state requests the next state becomes active instead
	 * @return true
	 * @return false
	 */
	const bool &nextState() const;

	/**
	 * @brief Returns the value of the 'exit' flag
	 *
	 * If true the state requests that the window / application be terminated
	 * @return true
	 * @return false
	 */
	const bool &exit() const;

protected:
	/**
	 * @brief An entity manager belnging to the state
	 *
	 */
	EntityManager entityManager_;

	/**
	 * @brief If true the state requests to be rendered under the currently active state
	 *
	 */
	bool renderWithAbove_;

	/**
	 * @brief  If true the state allows for the state beneath to be rendered with it
	 *
	 */
	bool renderBelow_;

	/**
	 * @brief If true the state requests the next state becomes active instead
	 *
	 */
	bool nextState_;

	/**
	 * @brief If true the state requests that the window / application be terminated
	 *
	 */
	bool exit_;
};