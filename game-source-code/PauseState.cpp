#include "PauseState.h"

PauseState::PauseState(const sf::Vector2f &windowSize)
{
	pauseImage_ = make_shared<sf::Texture>();

	if (!pauseImage_->loadFromFile(resourcePath() + "Images/paused.png"))
	{
		std::__throw_runtime_error("Couldn't load Pause image");
	}

	pause_ = make_shared<sf::Sprite>();
	float scalex = windowSize.x / (float)pauseImage_->getSize().x;
	float scaley = windowSize.y / (float)pauseImage_->getSize().y;

	pause_->scale(scalex, scaley);

	pause_->setTexture(*pauseImage_);

	renderBelow_ = true;
	pauseDelay_ = 0.2f;
}

const vector<Drawable_ptr> PauseState::getDrawable()
{
	return vector<Drawable_ptr>{pause_};
}

void PauseState::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pauseDelay_ <= 0)
	{
		nextState_ = true;
		pauseDelay_ = 0.2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		exit_ = true;
	}
}

void PauseState::update(const sf::Time &time)
{
	if (pauseDelay_ > 0)
	{
		pauseDelay_ -= time.asSeconds();
	}
}
