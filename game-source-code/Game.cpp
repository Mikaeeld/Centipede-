#include "Game.h"

Game::Game() : window_("Game", sf::Vector2u{960, 900}, 60), tickRate_(240.0f)
{
    frametime_ = 1.0f / tickRate_;
    state_ = GameState::splash;
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

    entityManager_.addEntity(GameEntity::entityType::Ship, sf::Vector2f{120.0f, 150.0f});
    entityManager_.addEntity(GameEntity::entityType::Mushroom, sf::Vector2f{120.0f, 150.0f});
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
        entityManager_.tick(elapsed_);
        elapsed_ = sf::seconds(0.0);
    }
}

void Game::render()
{
    window_.beginDraw();
    switch (state_)
    {
    case GameState::play:
    {

        for (auto i : entityManager_.getEntities())
        {
            window_.draw(*i);
        }
        break;
    }

    case GameState::splash:
    {
        window_.draw(splash_);
        break;
    }

    default:
        //none
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
    case GameState::play:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window_.close();
        }
        break;
    }

    case GameState::splash:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            state_ = GameState::play;
            window_.toggleBorderless();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window_.close();
        }
    }

    default:
        //none
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
