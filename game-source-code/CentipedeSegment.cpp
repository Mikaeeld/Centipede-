#include "CentipedeSegment.h"
#include "ResourcePath.h"

CentipedeSegment::CentipedeSegment(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back, const Speed_ptr speed)
{
	speed_ = speed;
	originAtCenter_ = true;
	triggerShot_ = false;
	const string base = resourcePath() + "Sprites/Centipede/";
	// Load Textures

	for (int i = 1; i <= 10; i++)
	{
		Texture_ptr headFrame(new sf::Texture);
		Texture_ptr bodyFrame(new sf::Texture);

		if (!headFrame->loadFromFile(base + "CentipedeHead" + to_string(i) + ".png"))
			throw std::runtime_error("Cannot Load Centipede Head Image");

		if (!bodyFrame->loadFromFile(base + "CentipedeBody" + to_string(i) + ".png"))
			throw std::runtime_error("Cannot Load Centipede Body Image");

		if (i <= 8)
		{
			addKeyFrame(KeyFrame{(i - 1) * KEYFRAME_INTERVAL, headFrame});
			addKeyFrame(KeyFrame{50.0f + ((i - 1) * KEYFRAME_INTERVAL), bodyFrame});
		}
		else if (i == 9) // turning texture
		{
			addKeyFrame(KeyFrame{NORMAL_RANGE + 1.0f, headFrame});
			addKeyFrame(KeyFrame{NORMAL_RANGE + 51.0f, bodyFrame});
		}
		else if (i == 10) // vertical texture
		{
			addKeyFrame(KeyFrame{NORMAL_RANGE + 2.0f, headFrame});
			addKeyFrame(KeyFrame{NORMAL_RANGE + 52.0f, bodyFrame});
		}
	}

	setPeriod(2.0f);
	setAnimateMode(AnimateMode::loop);

	updateChain(front, back);

	targetYDir_ = CentipedeMove::YDirection::Down;
	targetXDir_ = CentipedeMove::XDirection::Left;
	currentDir_ = CentipedeMove::Direction::Left;
}

float CentipedeSegment::manhattanDistance(const shared_ptr<CentipedeSegment> other) const
{
	return abs(other->getPosition().x - getPosition().x) + abs(other->getPosition().y - getPosition().y);
}

const sf::Vector2i CentipedeSegment::gridLocate()
{
	return sf::Vector2i(floor(getPosition().x / GameGrid::CELL_SIZE), floor(getPosition().y / GameGrid::CELL_SIZE));
}

void CentipedeSegment::updateChain(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back)
{
	front_ = front;
	back_ = back;

	// Check if there is no segment in front (nullptr)
	isHead_ = !front ? true : false;

	dynamic_ = isHead_;

	updateAnimation();
}

void CentipedeSegment::tick(const sf::Time &time)
{
	if (isHead_)
		updatePosition(time);

	if (triggerShot_)
	{
		triggerShot_ = false;
		shot();
	}

	updateAnimation();
}

void CentipedeSegment::updateAnimation()
{

	if (targetXDir_ == CentipedeMove::XDirection::Left)
		setRotation(0);
	else
		setRotation(180);

	if (isHead_)
		setAnimateTimings(0.0f, NORMAL_RANGE);
	else
		setAnimateTimings(50.0f, 50.0f + NORMAL_RANGE);
}

void CentipedeSegment::turn(const float &middleX)
{
	isTurning_ = true;

	auto yDiff = abs(middleX - getPosition().x);
	setPosition(middleX, getPosition().y);
	if (targetYDir_ == CentipedeMove::YDirection::Down)
	{
		move(0.0f, yDiff);
	}
	else
	{ // Up
		move(0.0f, -yDiff);
	}
}

#include <iostream>
void CentipedeSegment::handleTurn()
{
	auto targetX = (GameGrid::CELL_SIZE * targetTurnCell_.first) + GameGrid::HALF_CELL;
	auto targetY = (GameGrid::CELL_SIZE * targetTurnCell_.second) + GameGrid::HALF_CELL;

	auto diff = make_pair<float, float>(targetX - getPosition().x, targetY - getPosition().y);
	auto translate = sf::Vector2f{0.0f, 0.0f};

	if ((targetYDir_ == CentipedeMove::YDirection::Down && diff.second <= 0) || (targetYDir_ == CentipedeMove::YDirection::Up && diff.second >= 0))
	{
		float unit;
		if (targetYDir_ == CentipedeMove::YDirection::Down)
		{
			unit = diff.first < 0 ? 1.0f : -1.0f;
		}
		else
		{
			unit = diff.first < 0 ? -1.0f : 1.0f;
		}

		translate = sf::Vector2f{unit * diff.second, diff.second}; // undo Y overshoot and add it to x movement
		move(translate);
	}

	if ((targetXDir_ == CentipedeMove::XDirection::Left && diff.first >= 0) || (targetXDir_ == CentipedeMove::XDirection::Right && diff.first <= 0))
	{
		isTurning_ = false;
	}
}

void CentipedeSegment::initiateTurn()
{
	if (!isTurning_)
	{
		auto halfCell = GameGrid::CELL_SIZE / 2;
		float middleX;
		int turnTargetX;
		middleX = (gridLocate().x * GameGrid::CELL_SIZE) + halfCell;
		if (targetXDir_ == CentipedeMove::XDirection::Right)
		{												   // moving right
			targetXDir_ = CentipedeMove::XDirection::Left; // invert X direction
			turnTargetX = gridLocate().x - 1;
		}
		else
		{													// moving left
			targetXDir_ = CentipedeMove::XDirection::Right; // invert X direction
			turnTargetX = gridLocate().x + 1;
		}

		// Check if Y direction needs to be inverted
		if (targetYDir_ == CentipedeMove::YDirection::Down && getPosition().y > GameGrid::PLAYER_AREA_Y_MAX - GameGrid::CELL_SIZE)
		{
			targetYDir_ = CentipedeMove::YDirection::Up;
		}
		else if (targetYDir_ == CentipedeMove::YDirection::Up && (getPosition().y < GameGrid::PLAYER_AREA_Y_MIN + GameGrid::CELL_SIZE || getPosition().y < GameGrid::Y_MIN + GameGrid::CELL_SIZE))
		{
			targetYDir_ = CentipedeMove::YDirection::Down;
		}

		targetTurnCell_.first = turnTargetX;
		targetTurnCell_.second = gridLocate().y;

		if (targetYDir_ == CentipedeMove::YDirection::Down)
		{
			targetTurnCell_.second = targetTurnCell_.second + 1;
		}
		else
		{
			targetTurnCell_.second = targetTurnCell_.second - 1;
		}
		turn(middleX);
	}
}

void CentipedeSegment::checkGridBound()
{
	if (isTurning_)
	{ // Checking if turn is complete
		handleTurn();
	}
	else
	{ // Checking if X is out of bounds of grid

		auto halfCell = GameGrid::CELL_SIZE / 2;

		if (targetXDir_ == CentipedeMove::XDirection::Right)
		{ // moving right
			if (getPosition().x > GameGrid::X_MAX - halfCell)
				initiateTurn();
		}
		else
		{ // moving left
			if (getPosition().x < GameGrid::X_MIN + halfCell)
				initiateTurn();
		}

		auto it = tempCollisions_.begin();
		while (it != tempCollisions_.end())
		{
			auto cell = *it;
			auto loc = gridLocate();
			bool erase = false;
			if (cell.first == loc.x && cell.second == loc.y)
			{

				auto xTrigger = (cell.first * GameGrid::CELL_SIZE) + GameGrid::HALF_CELL;
				if (targetXDir_ == CentipedeMove::XDirection::Right)
				{ // moving right
					if (getPosition().x > xTrigger)
					{
						initiateTurn();
						erase = true;
					}
				}
				else
				{ // moving left
					if (getPosition().x < xTrigger)
					{
						initiateTurn();
						erase = true;
					}
				}
			}

			if (erase)
			{
				it = tempCollisions_.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}

void CentipedeSegment::updatePosition(const sf::Time &time)
{
	float distance;
	if (isTurning_)
	{
		distance = (targetYDir_ == CentipedeMove::YDirection::Down) ? 1.0f : -1.0f;
	}
	else
	{
		distance = (targetXDir_ == CentipedeMove::XDirection::Right) ? 1.0f : -1.0f;
	}
	distance *= *speed_ * time.asSeconds();
	auto translate = isTurning_ ? sf::Vector2f{0.0f, distance} : sf::Vector2f{distance, 0.0f};

	move(translate);

	checkGridBound();

	updateBack(time);
}

void CentipedeSegment::followFront(const sf::Time &time)
{
	if (front_)
	{
		if (isTurning_)
		{
			float distance = (targetYDir_ == CentipedeMove::YDirection::Down) ? 1.0f : -1.0f;
			distance *= *speed_ * time.asSeconds();
			auto translate = isTurning_ ? sf::Vector2f{0.0f, distance} : sf::Vector2f{distance, 0.0f};

			move(translate);
			checkGridBound();
		}
		else
		{
			if (front_->isTurning_)
			{
				float distance = (targetXDir_ == CentipedeMove::XDirection::Right) ? 1.0f : -1.0f;
				distance *= *speed_ * time.asSeconds();
				auto translate = isTurning_ ? sf::Vector2f{0.0f, distance} : sf::Vector2f{distance, 0.0f};

				move(translate);
				checkGridBound();
			}
			else
			{
				targetXDir_ = front_->targetXDir_;
				targetYDir_ = front_->targetYDir_;

				if (front_->targetXDir_ == CentipedeMove::XDirection::Left)
				{
					setPosition(front_->getPosition().x + 8, front_->getPosition().y);
				}
				else
				{
					setPosition(front_->getPosition().x - 8, front_->getPosition().y);
				}
			}
		}
	}
	else
	{
		throw runtime_error("Attempting to access null Front CentipedeSegment"); // should never reach this
	}
}

void CentipedeSegment::updateBack(const sf::Time &time)
{
	if (!isHead_)
	{
		followFront(time);
	}

	if (back_ != nullptr)
	{
		back_->updateBack(time);
	}
}

GameEntity::entityType CentipedeSegment::getType()
{
	return GameEntity::entityType::CentipedeSegment;
}

void CentipedeSegment::insertTempCollisionBack(const pair<int, int> location)
{

	if (back_ != nullptr)
	{
		back_->tempCollisions_.insert(location);
		back_->insertTempCollisionBack(location);
	}
}

void CentipedeSegment::clearTempCollisionBack()
{

	if (back_ != nullptr)
	{
		back_->tempCollisions_.clear();
		back_->clearTempCollisionBack();
	}
}

bool CentipedeSegment::handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other)
{
	(void)collisionRect;
	switch (type)
	{
	case entityType::Bullet:
	{ // split segment
		triggerShot_ = true;
		break;
	}
	case entityType::Explosion:
	{ // split segment
		shot();
		break;
	}
	case entityType::CentipedeSegment:
	{
		if (isHead_ && other && (collisionRect.width >= 4 && collisionRect.height >= 4))
		{

			auto isSelf = false;
			auto segment = back_;
			while (segment)
			{
				if (segment->getPosition() == other->getPosition())
				{
					isSelf = true;
					break;
				}
				segment = segment->back_;
			}

			if (!isSelf && !isTurning_)
			{

				// recursively push segment location to children
				auto loc = gridLocate();
				auto cell = pair<int, int>(loc.x, loc.y);
				tempCollisions_.insert(cell);
				insertTempCollisionBack(cell);
			}
		}
		return false;
		break;
	}
	case entityType::Mushroom:
	{

		if (isHead_ && (collisionRect.width >= 4 || collisionRect.height >= 4))
		{
			if (!isTurning_)
			{
				// recursively push mushroom location to children
				auto loc = gridLocate();
				auto cell = pair<int, int>(loc.x, loc.y);
				tempCollisions_.insert(cell);
				insertTempCollisionBack(cell);
			}
		}
		break;
	}
	default:
		// none
		return false;
		break;
	}

	return true;
}

void CentipedeSegment::shot()
{
	if (front_)
	{
		front_->updateChain(front_->front_, nullptr);
	}

	if (back_)
	{
		back_->updateChain(nullptr, back_->back_);
	}

	auto loc = gridLocate();

	if (!toDelete_)
	{
		loc.y = isTurning_ ? (targetYDir_ == CentipedeMove::YDirection::Down ? loc.y + 1 : loc.y - 1) : loc.y;
		createQueue_.push(pair<GameEntity::entityType, sf::Vector2f>{GameEntity::entityType::Mushroom, sf::Vector2f{loc.x * GameGrid::CELL_SIZE, loc.y * GameGrid::CELL_SIZE}});
	}
	toDelete_ = true;
}
