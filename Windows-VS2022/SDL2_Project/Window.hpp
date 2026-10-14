#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL2_Common.h"

class Window {

public:
    Window();
    ~Window();

    bool init();
    SDL_Window* getWindow();

    static const int WINDOW_WIDTH = 1920;
    static const int WINDOW_HEIGHT = 1080;

private:
    SDL_Window* window;
};

#endif