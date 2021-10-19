#include "PlayState.h"

PlayState::PlayState()
{
	// entityManager_ = EntityManager();

	ship_ = make_shared<Ship>(Ship());
	ship_->setPosition(sf::Vector2f{120.0f, 220.0f});

	playerArea_ = make_shared<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f{240.0f, 48.0f}));
	const sf::Color green(33, 71, 33);
	playerArea_->setFillColor(green);
	playerArea_->setPosition(0.0f, 200.0f);

	entityManager_.addEntity(GameEntity::entityType::Mushroom, sf::Vector2f{120.0f, 150.0f});

	entityManager_.addEntity(ship_);
	centipedeSpeed_ = Speed_ptr(new float(50.0f));
	// *centipedeSpeed_ = 0.0f;

	centipedeHead_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, centipedeSpeed_));
	centipedeBody_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(centipedeHead_, nullptr, centipedeSpeed_));

	centipedeHead_->updateChain(nullptr, centipedeBody_);

	centipedeHead_->setPosition(8 + 4, 2 + 4);
	centipedeBody_->setPosition(8 + 4, 2 + 4);
	entityManager_.addEntity(centipedeHead_);
	entityManager_.addEntity(centipedeBody_);
}

const vector<Drawable_ptr> PlayState::getDrawable()
{
	vector<Drawable_ptr> temp;
	temp.push_back(playerArea_);
	for (auto &entity : entityManager_.getEntities())
	{
		temp.push_back(static_cast<Drawable_ptr>(entity));
	}
	return temp;
}

void PlayState::update(const sf::Time &time)
{
	entityManager_.tick(time);
}