#include "Timer.h"

Timer::Timer() {
	start();
}

void Timer::start() {
	_start = millis();
}

void Timer::stop() {
	_end = millis();
}

int Timer::getDuration() const{
	return _end - _start;
}

int Timer::getDurationNow() const {
	return millis() - _start;
}