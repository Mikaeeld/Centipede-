#include "Game.h"
#include <iostream>

Game::Game() : window_("Game", sf::Vector2u{900, 960}, 0), tickRate_(120.0f)
{
    frametime_ = 1.0f / tickRate_;
    window_.toggleBorderless();

    auto windowSize = window_.getView().getSize();

    splashState_ = shared_ptr<SplashState>(new SplashState(windowSize));
    playState_ = shared_ptr<PlayState>(new PlayState());
    pauseState_ = shared_ptr<PauseState>(new PauseState(windowSize));
    gameOverState_ = shared_ptr<GameOverState>(new GameOverState(windowSize));

    scene_ = GameScene::splash;
    currentState_ = splashState_;
    nextState_ = playState_;
}

void Game::update()
{
    if (elapsed_.asSeconds() >= 0.2) // reset clock when elapsed is too large
    {
        elapsed_ = sf::seconds(0.0);
    }
    else if (elapsed_.asSeconds() >= frametime_)
    {
        handleInput();
        window_.update();
        currentState_->update(elapsed_);
        elapsed_ = sf::seconds(0.0);
        handleStateChange();
    }
}

void Game::render()
{
    window_.beginDraw();

    if (currentState_->renderBelow() && nextState_->renderWithAbove())
    {
        for (auto &item : nextState_->getDrawable())
        {
            window_.draw(*item);
        }
    }

    for (auto &item : currentState_->getDrawable())
    {
        window_.draw(*item);
    }

    window_.endDraw();
}

GameWindow *Game::getWindow()
{
    return &window_;
}

void Game::handleInput()
{
    currentState_->handleInput();
}

sf::Time Game::getElapsed()
{
    return elapsed_;
}

void Game::restartClock()
{
    elapsed_ += clock_.restart();
}

void Game::handleStateChange()
{
    if (currentState_->exit())
    {
        window_.close();
    }
    if (currentState_->nextState())
    {
        switch (scene_)
        {
        case GameScene::splash:
        {
            currentState_ = playState_;
            window_.toggleBorderless();
            scene_ = GameScene::play;
            break;
        }
        case GameScene::play:
        {
            nextState_ = playState_;
            playState_->reset();
            if (playState_->toDelete_)
            {
                currentState_ = gameOverState_;
                scene_ = GameScene::gameOver;
            }
            else
            {
                currentState_ = pauseState_;
                scene_ = GameScene::pause;
            }
            break;
        }
        case GameScene::pause:
        {
            currentState_ = playState_;
            pauseState_->reset();
            scene_ = GameScene::play;
            restartClock();
            break;
        }
        case GameScene::gameOver:
        {
            playState_ = shared_ptr<PlayState>(new PlayState());
            gameOverState_->reset();
            currentState_ = playState_;
            scene_ = GameScene::play;
            restartClock();
            break;
        }
        default:
            break;
        }
    }
}
