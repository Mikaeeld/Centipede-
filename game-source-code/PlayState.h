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

private:
	void spawnDDT(const sf::Time &time);
	void spawnSpider(const sf::Time &time);
	shared_ptr<Ship> ship_;
	shared_ptr<sf::RectangleShape> playerArea_;
	Speed_ptr centipedeSpeed_;
	Centipede centipede_;
	float ddtSpawnTime_ = 0.0f;
	float spiderSpawnTime_ = 0.0f;
};
