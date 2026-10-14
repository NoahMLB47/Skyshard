#include "Window.hpp"
#include "SDL2_Common.h"



Window::Window()
{
    window = nullptr;

}

Window::~Window()
{
    SDL_DestroyWindow(window);
    window = nullptr;
}

void Window::setWindow(SDL_Window* w)
{
    window = w;
}

SDL_Window* Window::getWindow()
{
    return window;
}

SDL_Window* Window::createSDLWindow()
{
    window = SDL_CreateWindow(
        "Hello GDV4001",          // Window title
        SDL_WINDOWPOS_UNDEFINED,  // X position
        SDL_WINDOWPOS_UNDEFINED,  // Y position
        WINDOW_WIDTH, WINDOW_HEIGHT,                 // width, height
        SDL_WINDOW_SHOWN);        // Window flags

    return window;
}
