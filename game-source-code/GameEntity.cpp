#include "GameEntity.h"
#include <memory>

GameEntity::GameEntity()
{
	animate_ = true;
	period_ = 1.0f;
	animateStart_ = 0.0f;
	animateEnd_ = period_;
	currentKeyFrame_ = 0;
	currentTime_ = 0;
	animateMode_ = AnimateMode::pause;
}

const KeyFrame GameEntity::getCurrentKeyFrame() const
{
	auto it = keyFrames_.begin();
	advance(it, currentKeyFrame_);
	return *it;
}

void GameEntity::removeKeyFrame(float percent)
{

	shared_ptr<sf::Texture> temp(new sf::Texture);
	keyFrames_.erase(KeyFrame(percent, temp));
}
