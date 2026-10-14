#include "Timer.hpp"
#include <memory>
#include "Game.hpp"

Timer::Timer()
{
}

Timer::~Timer()
{
}

float Timer::getDeltaTime()
{
	return timeDeltaInSeconds;
}

void Timer::update()
{
    currentTimeIndex = SDL_GetTicks();
    timeDelta = currentTimeIndex - prevTimeIndex; //time in milliseconds
    timeDeltaInSeconds = timeDelta * 0.001f; //time in seconds

    // Store current time index into prevTimeIndex for next frame
    prevTimeIndex = currentTimeIndex;
}



void Timer::init()
{
	prevTimeIndex = SDL_GetTicks();
}
