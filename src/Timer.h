#ifndef TIMER
#define TIMER

#include <stdint.h>

class Timer {
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	bool isStarted();
	bool isPaused();

	uint32_t ticks();

private:
	bool paused_;
	bool started_;
	uint32_t start_ticks_;
	uint32_t paused_ticks_;
};

#endif