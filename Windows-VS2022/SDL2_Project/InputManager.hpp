#pragma once
#include "SDL2_Common.h"
#include <memory>

class InputManager {

private: 
	const Uint8* keyStates;
	float horizontalInput;
	float verticalInput;
	SDL_Event event;
	bool quit;

	InputManager();
public:
	~InputManager();

	static std::shared_ptr<InputManager> instance()
	{
		static std::shared_ptr<InputManager> inputManager(new InputManager());
		inputManager->init();
		return inputManager;
	}
	float getHorizontalInput();
	float getVerticalInput();
	bool isWindowClosedEvent();
	void update();
	void init();
};