#pragma once
#include "SFML/Graphics.hpp"
#include "EntityManager.h"
#include "GameEntity.h"

using Drawable_ptr = shared_ptr<sf::Drawable>;

class State
{

public:
	State();

	virtual void update(const sf::Time &time);

	virtual void handleInput();

	virtual const vector<Drawable_ptr> getDrawable();

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