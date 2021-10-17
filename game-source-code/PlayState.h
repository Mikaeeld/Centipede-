#pragma once
#include "State.h"

class PlayState : public State
{
public:
	PlayState();

	const vector<Drawable_ptr> getDrawable();
	void update(const sf::Time &time);

private:
	shared_ptr<Ship> ship_;
	shared_ptr<sf::RectangleShape> playerArea_;
};
