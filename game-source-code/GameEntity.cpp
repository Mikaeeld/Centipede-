#include "GameEntity.h"
#include <memory>

GameEntity::GameEntity()
{
	animate_ = false;
	period_ = 1.0f;
	animateStart_ = 0.0f;
	animateEnd_ = 100.0f;
	currentTime_ = 0;
	animateMode_ = AnimateMode::pause;
}

set<KeyFrame>::iterator GameEntity::getKeyFrameAtPercent(const float &percent)
{
	auto itr = keyFrames_.begin();
	auto next = ++keyFrames_.begin();

	while ((*next).percent <= percent && (*itr).percent < percent)
	{
		itr++;
		if (++next == keyFrames_.end())
			return itr;
	}

	return itr;
}

#include <iostream>

const KeyFrame *GameEntity::getCurrentKeyFrame()
{

	if (keyFrames_.empty())
		throw NoKeyFrames{};

	if (animate())
	{
		auto percent = animateStart_ + (100.0f * currentTime_ / period_);
		itr_ = getKeyFrameAtPercent(percent);
	}
	else if (animateMode_ == AnimateMode::pause)
	{
		return &(*getKeyFrameAtPercent(animateStart_));
	}

	return &(*itr_);
}

void GameEntity::setAnimateMode(AnimateMode mode)
{
	animateMode_ = mode;
	currentTime_ = 0.0f;
	animate_ = animateMode_ == AnimateMode::pause ? false : true;

	auto current = GameEntity::getCurrentKeyFrame();
	GameEntity::setTexture(*current->texture, true);
	if (originAtCenter_)
	{
		GameEntity::setOrigin(sf::Vector2f(current->texture->getSize().x / 2, current->texture->getSize().y / 2));
	}
}

void GameEntity::removeKeyFrame(const float &percent)
{

	shared_ptr<sf::Texture> temp(new sf::Texture);
	keyFrames_.erase(KeyFrame(percent, temp));
}

void GameEntity::animateTick(sf::Time time)
{
	currentTime_ += time.asSeconds();

	auto calcPeriod = period_ * (animateEnd_ - animateStart_) / 100.0f;

	if (currentTime_ > calcPeriod)
	{
		currentTime_ = currentTime_ - calcPeriod;

		if (animateMode_ == AnimateMode::once)
		{
			animate_ = false;
		}
		else if (animateMode_ == AnimateMode::once_restart)
		{
			updateKeyFrame();
			animate_ = false;
			return;
		}
	}

	updateKeyFrame();
}

void GameEntity::updateKeyFrame()
{
	if (animate_)
	{
		auto current = GameEntity::getCurrentKeyFrame();
		GameEntity::setTexture(*current->texture, true);
		if (originAtCenter_)
		{
			GameEntity::setOrigin(sf::Vector2f(current->texture->getSize().x / 2, current->texture->getSize().y / 2));
		}
	}
}

void GameEntity::validateStartStopContraints()
{
	// 0 <= Start < End <= 100
	if (!(0.0f <= animateStart_ && animateStart_ < animateEnd_ && animateEnd_ <= 100.0f))
		throw InvalidAnimationTimings{};

	// Instead of only throwing exception invalid parameter could be wraped around to fit other parameters
}

void GameEntity::setAnimateStart(const float &start)
{
	animateStart_ = start;
	validateStartStopContraints();
}

void GameEntity::setAnimateEnd(const float &end)
{
	animateEnd_ = end;
	validateStartStopContraints();
}

void GameEntity::setPeriod(const float &period)
{
	period_ = period;
	// validateStartStopContraints();
}

bool GameEntity::collidesWith(GameEntity &other) const
{
	return getGlobalBounds().intersects(other.getGlobalBounds());
}