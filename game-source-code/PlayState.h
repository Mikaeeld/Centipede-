#pragma once
#include "State.h"
#include "Centipede.h"
#include "Random.h"
class PlayState : public State
{
public:
	PlayState();

	const vector<Drawable_ptr> getDrawable();
	void update(const sf::Time &time);
	bool toDelete_ = false;
	void spawnDDT(const sf::Time &time);

private:
	shared_ptr<Ship> ship_;
	shared_ptr<sf::RectangleShape> playerArea_;
	Speed_ptr centipedeSpeed_;
	Centipede centipede_;
	float ddtSpawnTime_ = 5.0f;
};
