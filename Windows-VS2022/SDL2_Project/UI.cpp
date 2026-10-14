#include "UI.hpp"
#include "TextBox.hpp"
#include "Vector3f.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "GameObjectFactory.hpp"
#include "Window.hpp"

#include <memory>

std::shared_ptr<UI> UI::ui = nullptr;

UI::UI()
{
    healthText = nullptr;
    scoreText = nullptr;
    score = 0;
}

UI::~UI()
{
    healthText.reset();
    healthText = nullptr;

    scoreText.reset();
    scoreText = nullptr;
}

std::shared_ptr<UI> UI::instance()
{
    if (!ui)
    {
        ui.reset(new UI());
        ui->init();
    }
    return ui;
}

void UI::init()
{
    healthText = GameObjectFactory::instance()->createTextBox("Health: 100", std::shared_ptr<Vector3f>(new Vector3f(Window::WINDOW_WIDTH * 0.0625f, Window::WINDOW_HEIGHT * 0.0231481481f, 0.0f)), Game::instance()->getRenderer()->getRenderer());
    scoreText = GameObjectFactory::instance()->createTextBox("Score: 0", std::shared_ptr<Vector3f>(new Vector3f(Window::WINDOW_WIDTH * 0.95f, Window::WINDOW_HEIGHT * 0.0231481481f, 0.0f)), Game::instance()->getRenderer()->getRenderer());
    
    gameOverText = GameObjectFactory::instance()->createTextBox("Game Over", std::shared_ptr<Vector3f>(new Vector3f(Window::WINDOW_WIDTH * 0.4f, Window::WINDOW_HEIGHT / 2.0f, 0.0f)), Game::instance()->getRenderer()->getRenderer());
    gameOverText->disable();

    levelCompleteText = GameObjectFactory::instance()->createTextBox("Level Complete", std::shared_ptr<Vector3f>(new Vector3f(Window::WINDOW_WIDTH * 0.4f, Window::WINDOW_HEIGHT / 2.0f, 0.0f)), Game::instance()->getRenderer()->getRenderer());
    levelCompleteText->disable();

}

void UI::updateHealth(std::string newHealth)
{
    healthText->updateMessage("Health: " + newHealth, Game::instance()->getRenderer()->getRenderer());
}

void UI::updateScore(int scoreAddition)
{
    score += scoreAddition;
    scoreText->updateMessage("Score: " + std::to_string(score), Game::instance()->getRenderer()->getRenderer());
}

void UI::enableGameOver()
{
    gameOverText->enable();
}

void UI::enableLevelComplete()
{
    levelCompleteText->enable();
}

