#include "Timer.h"

#include <SDL/SDL.h>

Timer::Timer() {
	start_ticks_ = 0;
	paused_ticks_ = 0;
	paused_ = false;
	started_ = false;
}

void Timer::start() {
	started_ = true;
	paused_ = false;

	// get the current clock time
	start_ticks_ = SDL_GetTicks();
	paused_ticks_ = 0;
}

void Timer::stop() {
	started_ = false;
	paused_ = false;

	start_ticks_ = 0;
	paused_ticks_ = 0;
}

void Timer::pause() {
	if (started_ && !paused_) {
		paused_ = true;

		// calculate the paused ticks
		paused_ticks_ = SDL_GetTicks() - start_ticks_;
		start_ticks_ = 0;
	}
}

void Timer::unpause() {
	if (started_ && paused_) {
		paused_ = false;
		start_ticks_ = SDL_GetTicks() - paused_ticks_;

		paused_ticks_ = 0;
	}
}

bool Timer::isStarted() {
	return started_;
}

bool Timer::isPaused() {
	return paused_ && started_;
}

uint32_t Timer::ticks() {
	uint32_t c_time = 0;

	if (started_) {
		if (paused_) {
			c_time = paused_ticks_; 
		}
		else {
			c_time = SDL_GetTicks() - start_ticks_;
		}
	}

	return c_time;
}