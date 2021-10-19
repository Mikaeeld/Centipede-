#include "Game.h"

Game::Game() : window_("Game", sf::Vector2u{900, 960}, 0), tickRate_(120.0f)
{
    frametime_ = 1.0f / tickRate_;
    state_ = GameScene::splash;
    window_.toggleBorderless();

    splashImage_ = textureManager_.getResource("Splash");
    if (splashImage_ == nullptr)
    {
        std::__throw_runtime_error("Couldn't load Splash image");
    }

    splash_.setTexture(*splashImage_);
    float scalex = (float)window_.getView().getSize().x / (float)splashImage_->getSize().x;
    float scaley = (float)window_.getView().getSize().y / (float)splashImage_->getSize().y;

    splash_.scale(scalex, scaley);
    
    gameoverImage_ = textureManager_.getResource("GameOver");
    if (gameoverImage_ == nullptr)
    {
        std::__throw_runtime_error("Couldn't load Splash image");
    }

    gameover_.setTexture(*gameoverImage_);
    scalex = (float)window_.getView().getSize().x / (float)gameoverImage_->getSize().x;
    scaley = (float)window_.getView().getSize().y / (float)gameoverImage_->getSize().y;

    gameover_.scale(scalex, scaley);
}

Game::~Game()
{
}

void Game::update()
{
    if (elapsed_.asSeconds() >= frametime_)
    {
        handleInput();
        window_.update();
        if (state_ == GameScene::play)
        {
            playState_.update(elapsed_);
            if (playState_.toDelete_)
            {
                state_ = GameScene::gameOver;
            }
        }
        elapsed_ = sf::seconds(0.0);
    }
}

void Game::render()
{
    window_.beginDraw();
    switch (state_)
    {
    case GameScene::play:
    {
        for (auto &i : playState_.getDrawable())
        {
            window_.draw(*i);
        }
        break;
    }

    case GameScene::splash:
    {
        window_.draw(splash_);
        break;
    }

    case GameScene::gameOver:
    {
        for (auto &i : playState_.getDrawable())
        {
            window_.draw(*i);
        }
        window_.draw(gameover_);
        break;
    }

    default:
        // none
        break;
    }

    window_.endDraw();
}

GameWindow *Game::getWindow()
{
    return &window_;
}

void Game::handleInput()
{

    switch (state_)
    {
    case GameScene::play:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window_.close();
        }
        break;
    }

    case GameScene::splash:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            state_ = GameScene::play;
            window_.toggleBorderless();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window_.close();
        }
    }

    case GameScene::gameOver:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            state_ = GameScene::play;
            playState_ = PlayState();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window_.close();
        }
    }

    default:
        // none
        break;
    }
}

sf::Time Game::getElapsed()
{
    return elapsed_;
}

void Game::restartClock()
{
    elapsed_ += clock_.restart();
}
