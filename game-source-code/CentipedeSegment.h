#pragma once

#include "GameEntity.h"
#include "SFML/Graphics.hpp"
#include "GameGrid.h"
#include <set>

using Speed_ptr = shared_ptr<float>;

namespace CentipedeMove
{
	enum class YDirection
	{
		Up = 1,
		Down
	};
	enum class XDirection
	{
		Left = 1,
		Right
	};
	enum class Direction
	{
		Up = 1,
		Down,
		Left,
		Right
	};
}

class CentipedeSegment : public GameEntity
{
public:
	CentipedeSegment(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back, const Speed_ptr speed);
	void tick(const sf::Time &time);
	void setSpeed(const float &speed);
	const float &getSpeed() const;
	const bool &isHead() const { return isHead_; }

	constexpr static const float NORMAL_RANGE = 40.0f;
	constexpr static const float KEYFRAME_INTERVAL = NORMAL_RANGE / 8.0f;

	/**
	 * @brief Used to initalize segment in the chain of segments making the CentipedeMove.
	 *
	 *  Ensures that there is always one head per centipde.
	 *
	 * @param front
	 * @param back
	 */
	void updateChain(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back);

	GameEntity::entityType getType();

	bool handleCollision(entityType type, sf::FloatRect collisionRect);

private:
	shared_ptr<CentipedeSegment> front_;
	shared_ptr<CentipedeSegment> back_;
	bool isHead_;
	bool isTurning_;
	CentipedeMove::YDirection targetYDir_;
	CentipedeMove::XDirection targetXDir_;
	CentipedeMove::Direction currentDir_;
	float manhattanDistance(const shared_ptr<CentipedeSegment> other) const;
	const bool &headTurning() const;
	Speed_ptr speed_;
	pair<int, int> targetTurnCell_;

	set<pair<int, int>> tempCollisions_;

	/**
	 * @brief Is called if segment is a head
	 *
	 * @param time
	 */
	void updatePosition(const sf::Time &time);

	/**
	 * @brief Updates each preceding segment recursively, and terminates at the end of the chain.
	 *
	 */
	void updateBack(const sf::Time &time);

	void insertTempCollisionBack(const pair<int, int> location);
	void clearTempCollisionBack();

	/**
	 * @brief Checks if the movement of the centipede is grid bound, corrects if not
	 *
	 *  The centipede will move within a grid, and will only turn at certain intervals
	 */
	void checkGridBound();

	void updateAnimation();

	void initiateTurn();
	void turn(const float &middleX);

	void handleTurn();

	void followFront(const sf::Time &time);

	void shot();

	const sf::Vector2i gridLocate();
};