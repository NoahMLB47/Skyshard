#include "InputManager.hpp"

InputManager::InputManager()
{
	keyStates = SDL_GetKeyboardState(NULL);
}

InputManager::~InputManager()
{
}


float InputManager::getHorizontalInput()
{
    // Process key states
    if (keyStates[SDL_SCANCODE_LEFT])
        horizontalInput = -1.0f;
    else
    {
        if (keyStates[SDL_SCANCODE_RIGHT])
            horizontalInput = 1.0f;
        else
            horizontalInput = 0.0f;
    }

	return horizontalInput;
}

float InputManager::getVerticalInput()
{
    // Process key states
    if (keyStates[SDL_SCANCODE_UP])
        verticalInput = -1.0f;
    else
    {
        if (keyStates[SDL_SCANCODE_DOWN])
            verticalInput = 1.0f;
        else
            verticalInput = 0.0f;
    }

	return verticalInput;
}

bool InputManager::isWindowClosedEvent()
{
    if (SDL_PollEvent(&event))  // test for events
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
    
    return quit;
}

void InputManager::update()
{

}

void InputManager::init()
{
}

