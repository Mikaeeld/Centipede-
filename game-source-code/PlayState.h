#pragma once
#include "State.h"
#include <random>
#include "Centipede.h"

class PlayState : public State
{
public:
	PlayState();

	const vector<Drawable_ptr> getDrawable();
	void update(const sf::Time &time);
	template <typename Prob>
	bool binomial_trial(const Prob p = 0.5)
	{
		static auto dev = std::random_device();
		static auto gen = std::mt19937{dev()};
		static auto dist = std::uniform_real_distribution<Prob>(0, 1);
		return (dist(gen) < p);
	}
	bool toDelete_ = false;

private:
	shared_ptr<Ship> ship_;
	shared_ptr<sf::RectangleShape> playerArea_;
	Speed_ptr centipedeSpeed_;
	Centipede centipede_;
};
