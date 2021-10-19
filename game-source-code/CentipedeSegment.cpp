#include "CentipedeSegment.h"
#include "ResourcePath.h"

CentipedeSegment::CentipedeSegment(const shared_ptr<CentipedeSegment> front, const shared_ptr<CentipedeSegment> back, const Speed_ptr speed)
{
	speed_ = speed;
	originAtCenter_ = true;
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

	targetYDir_ = Centipede::YDirection::Down;
	targetXDir_ = Centipede::XDirection::Left;
	currentDir_ = Centipede::Direction::Left;
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
	if (isHead_)
	{
		setAnimateStart(0.0f);
		setAnimateEnd(NORMAL_RANGE);
	}
	else
	{
		setAnimateStart(50.0f);
		setAnimateEnd(NORMAL_RANGE + 50.0f);
	}

	if (front_)
	{
		front_->back_ = make_shared<CentipedeSegment>(*this);
	}

	if (back_)
	{
		back_->front_ = make_shared<CentipedeSegment>(*this);
	}
}

void CentipedeSegment::tick(const sf::Time &time)
{
	if (isHead_)
		updatePosition(time);
}

void CentipedeSegment::updateTurnAnimation(const pair<float, float> &diff) {}

void CentipedeSegment::turn(const float &middleX)
{
	isTurning_ = true;

	auto yDiff = abs(middleX - getPosition().x);
	setPosition(middleX, getPosition().y);
	if (targetYDir_ == Centipede::YDirection::Down)
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

	// auto cLoc = gridLocate();

	auto diff = make_pair<float, float>(targetX - getPosition().x, targetY - getPosition().y);

	// std::cout << "diff: " << diff.first << ", " << diff.second << " Tcell: " << targetTurnCell_.first << ", " << targetTurnCell_.second << " YDir: " << Centipede::toString(targetYDir_) << " CLoc " << cLoc.x << ", " << cLoc.x << std::endl;

	auto translate = sf::Vector2f{0.0f, 0.0f};
	if ((targetYDir_ == Centipede::YDirection::Down && diff.second <= 0) || (targetYDir_ == Centipede::YDirection::Up && diff.second >= 0))
	{
		float unit;
		if (targetYDir_ == Centipede::YDirection::Down)
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

	if ((targetXDir_ == Centipede::XDirection::Left && diff.first >= 0) || (targetXDir_ == Centipede::XDirection::Right && diff.first <= 0))
	{
		isTurning_ = false;
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

		bool initiateTurn = false;
		auto halfCell = GameGrid::CELL_SIZE / 2;
		float middleX;
		int turnTargetX;

		if (targetXDir_ == Centipede::XDirection::Right)
		{ // moving right

			if (getPosition().x > GameGrid::X_MAX - halfCell)
			{ // initiate turn
				initiateTurn = true;
				targetXDir_ = Centipede::XDirection::Left; // invert X direction
				middleX = GameGrid::X_MAX - halfCell;
				turnTargetX = gridLocate().x - 1;
			}
		}
		else
		{ // moving left
			if (getPosition().x < GameGrid::X_MIN + halfCell)
			{ // initiate turn
				initiateTurn = true;
				targetXDir_ = Centipede::XDirection::Right; // invert X direction
				middleX = GameGrid::X_MIN + halfCell;
				turnTargetX = gridLocate().x + 1;
			}
		}

		if (initiateTurn)
		{
			// Check if Y direction needs to be inverted
			if (targetYDir_ == Centipede::YDirection::Down && getPosition().y > GameGrid::PLAYER_AREA_Y_MAX - GameGrid::CELL_SIZE)
			{
				targetYDir_ = Centipede::YDirection::Up;
			}
			else if (targetYDir_ == Centipede::YDirection::Up && (getPosition().y < GameGrid::PLAYER_AREA_Y_MIN + GameGrid::CELL_SIZE || getPosition().y < GameGrid::Y_MIN + GameGrid::CELL_SIZE))
			{
				targetYDir_ = Centipede::YDirection::Down;
			}

			targetTurnCell_.first = turnTargetX;
			targetTurnCell_.second = gridLocate().y;
			if (targetYDir_ == Centipede::YDirection::Down)
			{
				targetTurnCell_.second = targetTurnCell_.second + 1;
			}
			else
			{
				targetTurnCell_.second = targetTurnCell_.second - 1;
			}
			// targetTurnCell_.second += (targetYDir_ == Centipede::YDirection::Down) ? 1 : -1;
			turn(middleX);
		}
	}
}

void CentipedeSegment::updatePosition(const sf::Time &time)
{
	float distance;
	if (isTurning_)
	{
		distance = (targetYDir_ == Centipede::YDirection::Down) ? 1.0f : -1.0f;
	}
	else
	{
		distance = (targetXDir_ == Centipede::XDirection::Right) ? 1.0f : -1.0f;
	}
	distance *= *speed_ * time.asSeconds();
	auto translate = isTurning_ ? sf::Vector2f{0.0f, distance} : sf::Vector2f{distance, 0.0f};

	move(translate);

	checkGridBound();

	updateBack();
}

void CentipedeSegment::followFront()
{
	if (front_)
	{
		// std::cout << "Following..." << std::endl;
		auto diff = sf::Vector2f{front_->getPosition().x - getPosition().x, front_->getPosition().y - getPosition().y};

		std::cout << "Following... " << diff.x << "      " << diff.y << std::endl;

		// setPosition(front_->getPosition().x + 8, front_->getPosition().y);

		// if (diff.y != 0.0f)
		// { // Front segment has turned

		// 	if (diff.y >= GameGrid::CELL_SIZE)
		// 	{ // will have to turn

		// 		targetTurnCell_ = front_->targetTurnCell_;
		// 		targetXDir_ = front_->targetXDir_;
		// 		targetYDir_ = front_->targetYDir_;
		// 		auto middleX = gridLocate().x + GameGrid::CELL_SIZE / 2;
		// 		turn(middleX);
		// 	}
		// 	else if (isTurning_)
		// 	{ // convert dx to dy
		// 		auto magX = abs(diff.x);
		// 		diff.y += diff.y > 0 ? -(GameGrid::CELL_SIZE + magX) : GameGrid::CELL_SIZE + magX;
		// 		move(0.0f, diff.y);
		// 		handleTurn();
		// 	}
		// 	else
		// 	{ // convert dy to dx
		// 		auto magY = abs(diff.y);
		// 		diff.x += diff.x > 0 ? -(GameGrid::CELL_SIZE + magY) : GameGrid::CELL_SIZE + magY;
		// 		move(diff.x, 0.0f);
		// 	}
		// }
		// else
		// { // Just follow
		// 	diff.x += diff.x > 0 ? -GameGrid::CELL_SIZE : GameGrid::CELL_SIZE;
		// 	move(diff);
		// }
	}
	else
	{
		throw runtime_error("Attempting to access null Front CentipedeSegment"); // should never reach this
	}
}

void CentipedeSegment::updateBack()
{
	if (!isHead_)
	{
		followFront();
	}

	if (back_ != nullptr)
	{
		back_->updateBack();
	}
}
