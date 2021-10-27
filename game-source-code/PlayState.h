#pragma once
#include "State.h"
#include "Centipede.h"
#include "Random.h"
/**
 * @brief Gameplay state
 * 
 * The main gameplay loop
 * Spawns the required gameplay elements
 * Ends the game when end game conditions are met
 * 
 */
class PlayState : public State
{
public:
	/**
	 * @brief Construct a new Play State object
	 * 
	 */
	PlayState();

	/**
	 * @brief Get all drawable objects contained in the state
	 * 
	 * @return const vector<Drawable_ptr> 
	 */
	const vector<Drawable_ptr> getDrawable();

	/**
	 * @brief Updates gameplay loop and entities therein
	 * 
	 * @param time 
	 */
	void update(const sf::Time &time);
	
	/**
	 * @brief whether the state should be deleted. i.e. is the game over
	 * 
	 */
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
