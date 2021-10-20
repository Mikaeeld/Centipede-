#pragma once
#include "SFML/Graphics.hpp"
#include "EntityManager.h"
#include "GameEntity.h"

using Drawable_ptr = shared_ptr<sf::Drawable>;

class State
{

public:
	virtual void update(const sf::Time &time)
	{
		(void)time;
	};

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