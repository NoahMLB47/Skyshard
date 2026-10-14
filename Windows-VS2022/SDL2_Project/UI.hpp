#ifndef UI_HPP
#define UI_HPP

#include "SDL2_Common.h"
#include <memory>
#include <string>

class TextBox;

class UI {

public:
    ~UI();

    static std::shared_ptr<UI> instance();
    void init();
    void updateHealth(std::string newHealth);
    void updateScore(int scoreAddition);
    void enableGameOver();
    void enableLevelComplete();

private:
    UI();
    static std::shared_ptr<UI> ui;
    std::shared_ptr<TextBox> healthText;
    std::shared_ptr<TextBox> scoreText;
    std::shared_ptr<TextBox> gameOverText;
    std::shared_ptr<TextBox> levelCompleteText;

    int score;
};

#endif