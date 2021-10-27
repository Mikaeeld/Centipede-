#include "GameOverState.h"

GameOverState::GameOverState(const sf::Vector2f &windowSize)
{
	gameOverImage_ = make_shared<sf::Texture>();

	if (!gameOverImage_->loadFromFile(resourcePath() + "Images/gameover.png"))
	{
		std::__throw_runtime_error("Couldn't load Game Over image");
	}

	float scalex = windowSize.x / (float)gameOverImage_->getSize().x;
	float scaley = windowSize.y / (float)gameOverImage_->getSize().y;

	renderBelow_ = true;

	gameOver_ = make_shared<sf::Sprite>();
	gameOver_->scale(scalex, scaley);

	gameOver_->setTexture(*gameOverImage_);
}

const vector<Drawable_ptr> GameOverState::getDrawable()
{
	return vector<Drawable_ptr>{gameOver_};
}

void GameOverState::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		exit_ = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		nextState_ = true;
	}
}