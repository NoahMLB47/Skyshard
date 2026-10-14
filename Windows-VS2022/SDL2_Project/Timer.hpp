#pragma once
#include "SDL2_Common.h"
#include <memory>

class Timer {

private:
	unsigned int currentTimeIndex;
	unsigned int prevTimeIndex;
	unsigned int timeDelta;
	float timeDeltaInSeconds;
	Timer();

public:
	~Timer();

	static std::shared_ptr<Timer> instance()
	{
		static std::shared_ptr<Timer> timer(new Timer());
		return timer;
	}
	float getDeltaTime();
	void update();
	void init();
};
