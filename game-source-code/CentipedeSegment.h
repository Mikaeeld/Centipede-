#pragma once

#include "GameEntity.h"
#include "SFML/Graphics.hpp"
#include "GameGrid.h"
#include <set>

using Speed_ptr = shared_ptr<float>;

/**
 * @brief A namespace to define movement characteristics for the Centipede
 *
 */
namespace CentipedeMove
{
	/**
	 * @brief A list of Vertical (Y-axis) movements
	 *
	 * UP or Down
	 */
	enum class YDirection
	{
		Up = 1,
		Down
	};

	/**
	 * @brief A list of Horizontal (X-axis) movements
	 *
	 * Left or Right
	 */
	enum class XDirection
	{
		Left = 1,
		Right
	};

	/**
	 * @brief A list of 2-Dimensional axial movements
	 *
	 * Up, Down, Left or Right
	 */
	enum class Direction
	{
		Up = 1,
		Down,
		Left,
		Right
	};
}

/**
 * @brief Centipede Segment Game Entity
 *
 * This class implements the functionality of Centipede Segments which together make up a centipede
 * A segment could either be a Head or a Body, however a body Segment could become a head.
 * It is required that a centipede head moves horizontally until it collides with a boundary
 * (a wall or another entity: eg. a mushroom) which then it moves vertically and reverses it's horrizontal direction.
 *
 * When a centipede segment is shot it turns into a mushroom, and in essence the whole cetipede 'splits'. From the perspective
 * of head and body segments when a segment is shot the segment behind it becomes a head.
 *
 */
class CentipedeSegment : public GameEntity
{
public:
	/**
	 * @brief Construct a new Centipede Segment Game Entity
	 *
	 * @param speed The shared pointer to the speed of the Centipede Segment
	 */
	CentipedeSegment(const Speed_ptr speed);

	void tick(const sf::Time &time);

	/**
	 * @brief Returns true if the segment is a Head
	 *
	 * @return true
	 * @return false
	 */
	const bool &isHead() const { return isHead_; }

	/**
	 * @brief Range at wich the normal (walking) Animation Key Frames exist
	 *
	 */
	constexpr static const float NORMAL_RANGE = 40.0f;

	/**
	 * @brief Interval at wich to divide the Key Frames for walking (normal)
	 *
	 */
	constexpr static const float KEYFRAME_INTERVAL = NORMAL_RANGE / 8.0f;

	/**
	 * @brief Used to initalize segment in the chain of segments make the Centipede.
	 *
	 *  Ensures that there is always one head per centipde.
	 *
	 * @param front Segment in front (if nullptr then is head of Centipede)
	 * @param back Segment behind (can be nullptr, then is 'tail' of Centipede)
	 */
	void updateChain(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back);

	/**
	 * Re-implemented
	 *
	 * Returns CentipedeSegment type
	 *
	 */
	GameEntity::entityType getType();

	/**
	 * Re-implemented
	 *
	 * Handles Collisions with  Mushrooms, Bullets, Explosions, and other Segments
	 *
	 */
	bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other);

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
	bool triggerShot_;

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

	/**
	 * @brief Recursivley pushes a temporary collision location to child segments
	 *
	 * @param location
	 */
	void insertTempCollisionBack(const pair<int, int> location);
	void clearTempCollisionBack();

	/**
	 * @brief Checks if the movement of the centipede is grid bound, corrects if not
	 *
	 *  The centipede will move within a grid, and will only turn at certain intervals
	 */
	void checkGridBound();

	/**
	 * @brief Udates the Animation Start and End to set texture according to if the Segment is a Head or Body
	 *
	 */
	void updateAnimation();

	/**
	 * @brief Used to begin a turn handling  direction changes
	 *
	 */
	void initiateTurn();

	/**
	 * @brief Begins a turn
	 *
	 * @param middleX
	 */
	void turn(const float &middleX);

	/**
	 * @brief Updates posision of Segment while turning
	 *
	 */
	void handleTurn();

	/**
	 * @brief Updates the posision of child Segments recursively
	 *
	 * Called by a head segment
	 *
	 * @param time
	 */
	void followFront(const sf::Time &time);

	/**
	 * @brief Begins the dying process
	 *
	 */
	void shot();

	/**
	 * @brief Locates the Segment According to the Game Grid
	 *
	 * @return const sf::Vector2i
	 */
	const sf::Vector2i gridLocate();
};