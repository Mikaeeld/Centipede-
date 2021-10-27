#include "State.h"

State::State()
{
	renderWithAbove_ = false;
	renderBelow_ = false;
	nextState_ = false;
	exit_ = false;
}

void State::handleInput()
{
	// do nothing
}

void State::update(const sf::Time &time)
{
	(void)time;
}

const vector<Drawable_ptr> State::getDrawable()
{
	vector<Drawable_ptr> out(entityManager_.getEntities().size());
	for (auto &entity : entityManager_.getEntities())
	{
		if (auto temp = dynamic_pointer_cast<sf::Drawable>(entity))
			out.push_back(temp);
	}
	return out;
}

const bool &State::renderBelow() const
{
	return renderBelow_;
}

const bool &State::renderWithAbove() const
{
	return renderWithAbove_;
}

const bool &State::nextState() const
{
	return nextState_;
}

const bool &State::exit() const
{
	return exit_;
}

void State::reset()
{
	nextState_ = false;
	exit_ = false;
}
