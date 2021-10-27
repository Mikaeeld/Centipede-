#include "SplashState.h"

SplashState::SplashState(const sf::Vector2f &windowSize)
{
	splashImage_ = make_shared<sf::Texture>();

	if (!splashImage_->loadFromFile(resourcePath() + "Images/splash.png"))
	{
		std::__throw_runtime_error("Couldn't load Splash image");
	}

	splash_ = make_shared<sf::Sprite>();

	float scalex = windowSize.x / (float)splashImage_->getSize().x;
	float scaley = windowSize.y / (float)splashImage_->getSize().y;

	splash_->scale(scalex, scaley);

	splash_->setTexture(*splashImage_);
}

const vector<Drawable_ptr> SplashState::getDrawable()
{
	return vector<Drawable_ptr>{splash_};
}

void SplashState::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		nextState_ = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		exit_ = true;
	}
}